/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

// include guards
#ifndef HEADER_HPP
#define HEADER_HPP

#include "SHA256.hpp"
#include <chrono>
#include <ostream>
#include <stdint.h>

using milliseconds = std::chrono::milliseconds;

// Block header
class Header {
protected:
	// The version of the block
	int version = 1;
	// Pointer to the hash of the prevoius block
	uint8_t* previousHash = new uint8_t[SHA256::SIZE];
	// Pointer to the hash of the merkle root
	uint8_t* merkleRootHash = new uint8_t[SHA256::SIZE];
	// Unix time at which the block was created
	uint64_t createdAt = std::chrono::duration_cast<milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	int nonce; // needed for PoW

	friend std::ostream& operator<<(std::ostream& s, const Header& header);

public:
	Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash);
	Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash);
	Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt);
	Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt);
	~Header();

	uint8_t* getPreviousHash();
	uint8_t* getMerkleRootHash();
};

#endif