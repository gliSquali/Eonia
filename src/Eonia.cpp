#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "Hash.hpp"
#include "Block.hpp"
#include "Common.hpp"
#include "Blockchain.hpp"
#include "Requests.hpp"

#include "json.hh"
using json = nlohmann::json;

using namespace std;

#include "client_http.hpp"
#include "server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

/*
Hash header: index + prevHash + merkleRoot(data) + nonce
*/

int main() {
    HttpServer server;

    int port;
    printf("Enter port: ");
    scanf("%d",&port);
    server.config.port = port; //server port

    vector<int> listOfNodes; //vector of the ports of nodes in the network

    char ch;
    printf("Initial Node? (y or n) ");
    scanf(" %c", &ch);
    Blockchain bc;
    if (ch == 'y'){
        // setup with genesis block
        bc = Blockchain(0);
    }
    else if(ch =='n'){
        // New Node - need to add self to network by providing ports
        bc = Blockchain(0);

        char otherPorts[50];
        // Example input: 8000,3000,3030
        printf("Enter ports of nodes in network(with commas in between): ");
        scanf("%s", otherPorts);
        stringstream ss(otherPorts);
        int i;
        while(ss >> i) {
            listOfNodes.push_back(i);
            if(ss.peek() == ',' || ss.peek() == ' ')
                ss.ignore();
        };

        addSelfToNetwork(&listOfNodes, server.config.port);
        json chain = getChainFromNodes(&listOfNodes);
        //skips first block, same genesis
        for(int i = 1; i < chain["length"].get<int>(); i++ ){
            auto block = chain["data"][i];
            vector<string> data = block["data"].get<vector<string>>();
            bc.addBlock(block["index"], block["previousHash"], block["hash"], block["nonce"], data);
        };
    }
    else {
        return 0;
    }

    // POST /addnode - used to add node to network, called by new node to all the nodes in the network

    server.resource["^/addnode$"]["POST"] = [&listOfNodes](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        printf("POST /addnode --- New Node adding to network....\n");
        try {
            json content = json::parse(request->content);
            int port = content["port"].get<int>();
            listOfNodes.push_back(port); // Adds port to listOfNodes
            printf("----Adding node %d to listOfNodes\n",port);
            response->write("Added You to our List");
        }
        catch(const exception &e) {
            *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        };
    };

    // GET /latestchain gets latest blockchain and sends it
    server.resource["^/latestchain$"]["GET"] = [&bc](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        printf("GET /latestchain --- Sending Blockchain....\n");
        response->write(bc.toJSON());
        printf("---Sent current Blockchain\n");
    };

    // POST /newchain called by a node when a new block is added to it
    server.resource["^/newchain$"]["POST"] = [&bc](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
        cout << "POST /newchain --- Node in Network sent new chain\n";
        try {
            json content = json::parse(request->content);
            if(content["length"].get<int>() > bc.getNumOfBlocks()) {
                bc.replaceChain(content);
                cout << "----Replaced current chain with new one" << endl;
                response->write("Replaced Chain\n");
            }
            else {
                cout << "----Chain was not replaced: sent chain had same size" << endl;
                response->write("Same Chain Size -- invalid");
            };
        }
        catch(const exception &e) {
            *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        };
    };

    // On error lambda function
    server.on_error = [](shared_ptr<HttpServer::Request>, const SimpleWeb::error_code & ec) {
        if(ec.message() != "End of file") {
            cout << "SERVER ERROR: " << ec.message() << endl;
        };
      };
    printf("Starting server at %d", server.config.port);

    // start server
    thread server_thread([&server]() {
        server.start();
    });

    // infinite loop
    while(true) {
        vector<string> v;
        int temp;

        printf("\n(1) Look at Blocks \n(2) Add block\n");
        int valid = scanf("%d", &temp);

        if((valid == 1) && (temp == 1)) {
            printf("What Block do you want to look at? ");
            scanf("%d", &temp);
            try {
                bc.getBlock(temp).toString();
            }
            catch (const exception& e){
                cout << e.what() << endl;
            };
        }
        else if (temp == 2) {
            char tmp[201];
            printf("\nADDING BLOCKS!\nEnter your message: ");
            scanf("%200s", tmp);
            string str = tmp;
            printf("Entered '%s' into block\n", str.c_str());
            v.push_back(str);

            try {
                if(bc.getNumOfBlocks() == 0) {
                    printf("----------------------------------\nPlease join the network... Your blockchain doesn't have any blocks ");
                    continue;
                }
                // mine for the hash
                auto pair = findHash(bc.getNumOfBlocks(), bc.getLatestBlockHash(), v);
                // add the block to the blockchain
                bc.addBlock(bc.getNumOfBlocks(), bc.getLatestBlockHash(), pair.first, pair.second, v);
                // send the blockchain to the network
                sendNewChain(&listOfNodes, bc.toJSON());
            }
            catch(const exception& e) {
                cout << e.what() << "\n" << endl;
            };
        };
    };

    printf("\n");
    return 0;
};