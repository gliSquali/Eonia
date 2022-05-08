/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

#include "Header.hpp"

#include "SHA256.hpp"
#include <chrono>
#include <ostream>
#include <stdint.h>


Header::Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash) {
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->previousHash[i] = sPreviousHash[i];
		this->merkleRootHash[i] = sMerkleRootHash[i];
	};
	return;
};

Header::Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash): Header(sPreviousHash, sMerkleRootHash) {
	this->version = sVersion;
	return;
};

Header::Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRoot, uint64_t sCreatedAt): Header(sVersion, sPreviousHash, sMerkleRoot) {
	this->createdAt = sCreatedAt;
	return;
};

Header::Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt): Header(sPreviousHash, sMerkleRootHash) {
	this->createdAt = sCreatedAt;
};

Header::~Header() {
	delete[] this->previousHash;
	delete[] this->merkleRootHash;
	return;
};


std::ostream& operator<< (std::ostream& s, const Header& header) {
	return s << "{\n" <<
	"\"version\": \"" << header.version << "\"\n" <<
	"\"previousHash\": \"" << SHA256::toString(header.previousHash) << "\"\n" <<
	"\"merkleRootHash\": \"" << SHA256::toString(header.merkleRootHash) << "\"\n" <<
	"\"createdAt\": \"" << header.createdAt << "\"\n" <<
	"}\n";
};


uint8_t* Header::getPreviousHash() {
	return this->previousHash;
};

uint8_t* Header::getMerkleRootHash() {
	return this->merkleRootHash;
}