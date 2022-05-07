/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

// include guards
#ifndef HEADER_HPP
#define HEADER_HPP

#include <string>
#include <string.h>
#include <time.h>

using string = std::string;

// Block header
class Header {
protected:
	// The version of the block
	int version;
	// The hash of the prevoius block
	string previousHash;
	// The hash of the merkle root
	string merkleRootHash;
	// Unix time at which the block was created
	time_t time;
	int nonce; // needed for PoW

public:
	Header(int sVersion, string sPreviousHash, string sMerkleRoot, time_t sTime);
	~Header();

	string getPreviousHash();
	string getMerkleRootHash();
};

#endif