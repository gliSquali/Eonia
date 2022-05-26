#include "Blockchain.hpp"

#include <stdexcept>
#include <stdint.h>
#include <string>

#include "Block.hpp"
#include "Common.hpp"

Blockchain::Blockchain(bool genesis) {
	if(!genesis) {
		std::vector<std::string> v;
		v.push_back("Genesis Block!");
		auto hash_nonce_pair = findHash(0, std::string("00000000000000"), v);

		this->blockchain.push_back(std::make_unique<Block>(0, std::string("00000000000000"), hash_nonce_pair.first, hash_nonce_pair.second, v));
		std::cout << "Created blockchain!\n";
	};
};

Block Blockchain::getBlock(uint32_t index) {
	for(uint32_t i = 0; i < this->blockchain.size(); i++) {
		if(this->blockchain[i]->getIndex() == index) {
			return *(this->blockchain[i]);
		};
	};
	throw std::invalid_argument("Index does not exist.");
};

uint32_t Blockchain::length() {
	return this->blockchain.size();
};

bool Blockchain::addBlock(uint32_t sIndex, std::string sPrevHash, std::string sHash, std::string sNonce, std::vector<std::string>& sMerkle) {
	std::string header = std::to_string(sIndex) + sPrevHash + getMerkleRoot(sMerkle) + sNonce;
	//check whether hash meets criteria (is composed of header, starting with 00, has index == to last index + 1)
	if((!sha256(header).compare(sHash)) && (sHash.substr(0,2) == "00") && (sIndex == this->blockchain.size())) {
		printf("Block hashes match --- Adding Block %s \n", sHash.c_str());
		this->blockchain.push_back(std::make_unique<Block>(sIndex, sPrevHash, sHash, sNonce, sMerkle));
		return 1;
	};
	std::cout << "Hash doesn't match criteria\n";
	return 0;
};

std::string Blockchain::getLastHash() {
	return this->blockchain[this->blockchain.size() - 1]->getHash();
};

json Blockchain::toJSON() {
	json j;
	j["length"] = this->blockchain.size();
	for(uint32_t i = 0; i < this->blockchain.size(); i++) {
		j["data"][this->blockchain[i]->getIndex()] = this->blockchain[i]->toJSON();
	};
	return j.dump(3);
};

bool Blockchain::replaceChain(json sChain) {
	// remove all except first block
	while(this->blockchain.size() > 1) {
		this->blockchain.pop_back();
	};

	for(int i = 1; i < sChain["length"].get<int>(); i++) {
		json block = sChain["data"][i];
		std::vector<std::string> data = sChain["data"].get<std::vector<std::string>>();
		this->addBlock(block["index"], block["previousHash"], block["hash"], block["nonce"], data);
	};
	return 1;
};