/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

#include "Block.hpp"
#include <string>
#include <string.h>
#include <vector>

Block::Block(int sVersion, std::string sPreviousHash, std::string sMerkleRoot, time_t sTime, long sIndex, std::string sHash, std::vector<std::string> sTxs): Header(sVersion, sPreviousHash, sMerkleRoot, sTime) {
	this->index = sIndex;
	this->hash = sHash;
	this->txs = sTxs;
	this->NTx = sTxs.size();
};

Block::Block(int sVersion, std::string sPreviousHash, std::string sMerkleRoot, time_t sTime, long sIndex, std::vector<std::string> sTxs): Header(sVersion, sPreviousHash, sMerkleRoot, sTime) {
	this->index = sIndex;
	this->hash = "";
	this->txs = sTxs;
	this->NTx = sTxs.size();
};

Block::Block(Header sHeader, long sIndex, std::string sHash, std::vector<std::string> sTxs ): Header(sHeader) {
	this->index = sIndex;
	this->hash = sHash;
	this->txs = sTxs;
	this->NTx = sTxs.size();
};

Block::~Block() {};


long Block::getIndex() {
	return this->index;
};