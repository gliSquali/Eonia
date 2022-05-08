/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

#include "Block.hpp"

#include "SHA256.hpp"
#include "Header.hpp"
#include <ostream>
#include <string>
#include <vector>


Block::Block(Header sHeader, long sIndex, std::vector<uint8_t*> sTxs): Header(sHeader), index(sIndex), nTxs(sTxs.size()) {
	this->txs = sTxs;
	return;
};

Block::Block(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreateAt, long sIndex, std::vector<uint8_t*> sTxs): Block(Header(sPreviousHash, sMerkleRootHash, sCreateAt), sIndex, sTxs) {return;};

Block::~Block() {};


std::ostream& operator<< (std::ostream& s, const Block& block) {
	std::string transactions = "";
	for(auto tx: block.txs) {
		transactions += "\t\"" + SHA256::toString(tx) + "\",\n";
	}
	return s << "{\n" <<
	"\"version\": \"" << block.version << "\"\n" <<
	"\"previousHash\": \"" << SHA256::toString(block.previousHash) << "\"\n" <<
	"\"merkleRootHash\": \"" << SHA256::toString(block.merkleRootHash) << "\"\n" <<
	"\"createdAt\": \"" << block.createdAt << "\"\n" <<
	"\"index\": \"" << block.index << "\"\n" <<
	"\"hash\": \"" << SHA256::toString(block.hash) << "\"\n" <<
	"\"numberOfTransactions\": \"" << block.nTxs << "\"\n" <<
	"\"transactions\": {\n" <<
	transactions <<
	"}\n" <<
	"}\n";
};


long Block::getIndex() {
	return this->index;
};