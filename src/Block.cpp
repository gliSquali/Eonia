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


void Block::copyHash(uint8_t* sHash) {
	if(sHash == nullptr || sHash == NULL) {
		for(short i = 0; i < SHA256::SIZE; i++) {
			this->hash[i] = 0;
		};
		return;
	};
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->hash[i] = sHash[i];
	};
	return;
};


Block::Block(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt, unsigned long sIndex, uint8_t* sHash, std::vector<uint8_t*> sTxs): Header(sVersion, sPreviousHash, sMerkleRootHash, sCreatedAt), index(sIndex), txs(sTxs), nTxs(sTxs.size()) {
	this->hash = new uint8_t[SHA256::SIZE];
	this->copyHash(sHash);
};
Block::Block(int sVersion, const uint8_t* sPreviousHash, const uint8_t* sMerkleRootHash, uint64_t sCreatedAt, unsigned long sIndex, uint8_t* sHash, std::vector<uint8_t*> sTxs): Header(sVersion, sPreviousHash, sMerkleRootHash, sCreatedAt), index(sIndex), txs(sTxs), nTxs(sTxs.size()) {
	this->hash = new uint8_t[SHA256::SIZE];
	this->copyHash(sHash);
};

Block::Block(Header sHeader, unsigned long sIndex, uint8_t* sHash, std::vector<uint8_t*> sTxs): Header(sHeader), index(sIndex), txs(sTxs), nTxs(sTxs.size()) {
	this->hash = new uint8_t[SHA256::SIZE];
	this->copyHash(sHash);
};

Block::Block(Header sHeader, unsigned long sIndex, std::vector<uint8_t*> sTxs): Block(sHeader, sIndex, nullptr, sTxs) {return;};

Block::Block(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, unsigned long sIndex, std::vector<uint8_t*> sTxs): Block(1, sPreviousHash, sMerkleRootHash, std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count(), sIndex, nullptr, sTxs) {return;};
Block::Block(const uint8_t* sPreviousHash, const uint8_t* sMerkleRootHash, unsigned long sIndex, std::vector<uint8_t*> sTxs): Block(1, sPreviousHash, sMerkleRootHash, std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count(), sIndex, nullptr, sTxs) {return;};

Block::Block(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreateAt, unsigned long sIndex, std::vector<uint8_t*> sTxs): Block(1, sPreviousHash, sMerkleRootHash, sCreateAt, sIndex, nullptr, sTxs) {return;};


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


unsigned long Block::getIndex() {
	return this->index;
};