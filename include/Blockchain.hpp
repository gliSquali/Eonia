#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <iostream>
#include <string>
#include "Hash.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

#include "json.hh"
using json = nlohmann::json;

class Blockchain {
public:
	Blockchain(int genesis  = 1 );
	Block getBlock(int index);
	int getNumOfBlocks();
	int addBlock(size_t index, string prevHash, string hash, string nonce, vector<string> &merkle);
	string getLatestBlockHash();
	string toJSON();
	int replaceChain(json chain);
private:
	vector<unique_ptr<Block>> blockchain;
};

Blockchain::Blockchain(int genesis){
	if(genesis == 0) {
		vector<string> v;
		v.push_back("Genesis Block!");
		auto hash_nonce_pair = findHash(0, string("00000000000000"), v);

		this->blockchain.push_back(std::make_unique<Block>(0, string("00000000000000"), hash_nonce_pair.first, hash_nonce_pair.second, v));
		printf("Created blockchain!\n");
	};
};
// Gets block based on the index
Block Blockchain::getBlock(int index) {
	for(size_t i = 0; i < this->blockchain.size(); i++) {
		if(this->blockchain[i]->getIndex() == index) {
			return *(blockchain[i]);
		};
	};
	throw invalid_argument("Index does not exist.");
};

// returns number of blocks
int Blockchain::getNumOfBlocks() {
	return this->blockchain.size();
};

// checks whether data fits with the right hash -> add block
int Blockchain::addBlock(size_t index, string prevHash, string hash, string nonce, vector<string> &merkle) {
	string header = to_string(index) + prevHash + getMerkleRoot(merkle) + nonce;
	if((!sha256(header).compare(hash)) && (hash.substr(0,2) == "00" ) && (index == blockchain.size())) {
		printf("Block hashes match --- Adding Block %s \n", hash.c_str());
		this->blockchain.push_back(std::make_unique<Block>(index, prevHash, hash, nonce, merkle));
		return 1;
	};
	cout << "Hash doesn't match criteria\n";
	return 0;
};

// returns hash of the latest block, used for finding the previousHash when mining new block
string Blockchain::getLatestBlockHash() {
	return this->blockchain[blockchain.size() - 1]->getHash();
};

// returns JSON string of JSON - used to send to network
string Blockchain::toJSON() {
	json j;
	j["length"] = this->blockchain.size();
	for(size_t i = 0; i < this->blockchain.size(); i++){
		j["data"][this->blockchain[i]->getIndex()] = this->blockchain[i]->toJSON();
	};
	return j.dump(3);
};

// replaces Chain with new chain represented by a JSON, used when node sends new blockchain
int Blockchain::replaceChain(json chain) {
	//remove all blocks except for the first block
	while(this->blockchain.size() > 1) {
		this->blockchain.pop_back();
	};
	for (int i = 1; i < chain["length"].get<int>(); i++ ){
		auto block = chain["data"][i];
		vector<string> data = block["data"].get<vector<string>>();
		this->addBlock(block["index"], block["previousHash"], block["hash"], block["nonce"], data);
	};
	return 1;
};

#endif // BLOCKCHAIN_HPP