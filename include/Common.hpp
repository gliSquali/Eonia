#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

void print_hex(const char *label, const uint8_t *v, size_t len) {
	printf("%s: ", label);
	for(size_t i = 0; i < len; ++i) {
		printf("%02x", v[i]);
	};
	printf("\n");
};

string getMerkleRoot(const vector<string> &merkle) {
	printf("\nFinding Merkle Root.... \n");
	if(merkle.empty())
		return "";
	else if(merkle.size() == 1)
		return sha256(merkle[0]);

	vector<string> new_merkle = merkle;

	while(new_merkle.size() > 1) {
		if(new_merkle.size() % 2 == 1)
			new_merkle.push_back(merkle.back());

		vector<string> result;

		for(size_t i = 0; i < new_merkle.size(); i += 2) {
			string var1 = sha256(new_merkle[i]);
			string var2 = sha256(new_merkle[i+1]);
			string hash = sha256(var1+var2);
			result.push_back(hash);
		};
		new_merkle = result;
	};
	return new_merkle[0];
};

pair<string,string> findHash(int index, string prevHash, vector<string> &merkle) {
	string header = to_string(index) + prevHash + getMerkleRoot(merkle);
	for(unsigned int nonce = 0; nonce < 100000; nonce++ ) {
		string blockHash = sha256(header + to_string(nonce));
		if(blockHash.substr(0,2) == "00") {
			return make_pair(blockHash,to_string(nonce));
			break;
		;};
	};
	return make_pair("fail","fail");
};

#endif // COMMON_HPP