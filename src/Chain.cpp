/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

#include "Chain.hpp"

Chain::Chain() {
	this->chain.push_back(this->getGenesis());
};

Chain::~Chain() {};


Block Chain::getGenesis() {
	return Block(1, std::string(), "0x1bc3300000000000000000000000000000000000000000000", time(nullptr), 0, {});
};

Block Chain::getLast() {
	return chain.back();
};

Block Chain::get(long index) {
	return chain[index];
}

void Chain::add(Block sBlock) {
	Block prev = this->getLast();
	if(prev.getIndex() < sBlock.getIndex() && sBlock.getPreviousHash() == prev.getMerkleRootHash()) {
		this->chain.push_back(sBlock);
	}
}