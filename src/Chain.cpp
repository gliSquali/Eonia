/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

#include "Chain.hpp"

#include "Block.hpp"
#include "SHA256.hpp"
#include <stdint.h>
#include <string>
#include <vector>


const uint8_t Chain::emptyHash[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint8_t Chain::genesisMerkleRootHash[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xBC, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


Chain::Chain(std::string sName): name(sName), nBlocks(0) {
	this->blocks.assign(1, Chain::newGenesis());
};

Chain::~Chain() {};


std::string Chain::getName() {
	return this->name;
};

// generate new genesis block
Block Chain::newGenesis() {
	return Block(Chain::emptyHash, Chain::genesisMerkleRootHash, 0, std::vector<uint8_t*>());
};

Block Chain::getLast() {
	return this->blocks.back();
};

Block Chain::get(unsigned long index) {
	return this->blocks[index];
};

void Chain::add(Block sBlock) {
	Block prev = this->getLast();
	if(prev.getIndex() < sBlock.getIndex() && sBlock.getPreviousHash() == prev.getMerkleRootHash()) {
		this->blocks.push_back(sBlock);
	};
};