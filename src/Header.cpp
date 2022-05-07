/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

#include "Header.hpp"
#include <string>
#include <string.h>
#include <time.h>

Header::Header(int sVersion, std::string sPreviousHash, std::string sMerkleRoot, time_t sTime) {
	this->version = 1;
	this->previousHash = sPreviousHash;
	this->merkleRootHash = sMerkleRoot;
	this->time = sTime;
};

Header::~Header() {};


std::string Header::getPreviousHash() {
	return this->previousHash;
};

std::string Header::getMerkleRootHash() {
	return this->merkleRootHash;
}