/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

#include "Header.hpp"

#include "SHA256.hpp"
#include <chrono>
#include <ostream>
#include <stdint.h>


void Header::copyHashes(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash) {
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->previousHash[i] = sPreviousHash[i];
		this->merkleRootHash[i] = sMerkleRootHash[i];
	};
	return;
};

void Header::copyPrevious(uint8_t* sPreviousHash) {
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->previousHash[i] = sPreviousHash[i];
	};
	return;
};

void Header::copyMerkle(uint8_t* sMerkleRootHash) {
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->merkleRootHash[i] = sMerkleRootHash[i];
	};
	return;
};

void Header::copyHashes(const uint8_t* sPreviousHash, const uint8_t* sMerkleRootHash) {
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->previousHash[i] = sPreviousHash[i];
		this->merkleRootHash[i] = sMerkleRootHash[i];
	};
	return;
};

void Header::copyPrevious(const uint8_t* sPreviousHash) {
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->previousHash[i] = sPreviousHash[i];
	};
	return;
};

void Header::copyMerkle(const uint8_t* sMerkleRootHash) {
	for(short i = 0; i < SHA256::SIZE; i++) {
		this->merkleRootHash[i] = sMerkleRootHash[i];
	};
	return;
};


Header::Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRoot, uint64_t sCreatedAt) {
	this->version = sVersion;

	this->previousHash = new uint8_t[SHA256::SIZE];
	this->merkleRootHash = new uint8_t[SHA256::SIZE];
	this->copyHashes(sPreviousHash, sMerkleRoot);

	this->createdAt = sCreatedAt;
	return;
};

Header::Header(int sVersion, const uint8_t* sPreviousHash, const uint8_t* sMerkleRoot, uint64_t sCreatedAt) {
	this->version = sVersion;

	this->previousHash = new uint8_t[SHA256::SIZE];
	this->merkleRootHash = new uint8_t[SHA256::SIZE];
	this->copyHashes(sPreviousHash, sMerkleRoot);

	this->createdAt = sCreatedAt;
	return;
};

Header::Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash): Header(1, sPreviousHash, sMerkleRootHash, std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count()) {
	return;
};

Header::Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash): Header(sVersion, sPreviousHash, sMerkleRootHash, std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count()) {
	return;
};

Header::Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt): Header(1, sPreviousHash, sMerkleRootHash, sCreatedAt) {
	return;
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
};