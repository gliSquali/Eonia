#include "Blockchain.hpp"

#include <stdint.h>

#include "Block.hpp"
#include "Common.hpp"

Blockchain::Blockchain(bool genesis) {
	if(!genesis) {
		std::vector<std::string> v;
		v.push_back("Genesis Block!");
		auto hash_nonce_pair = findHash(0, std::string("00000000000000"),v);

		this -> blockchain.push_back(std::make_unique<Block>(0,string("00000000000000"),hash_nonce_pair.first,hash_nonce_pair.second,v));
		printf("Created blockchain!\n");
	};
};

Block Blockchain::getBlock(uint32_t index) {
	for(uint32_t i = 0; i < this->blockchain.size(); i++) {
		if(this->blockchain[i]->getIndex() == index) {
			return *(blockchain[i]);
		};
	};
	throw std::invalid_argument("Index does not exist.");
};