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
	int version;
	// Pointer to the hash of the prevoius block
	uint8_t* previousHash;
	// Pointer to the hash of the merkle root
	uint8_t* merkleRootHash;
	// Unix time at which the block was created
	uint64_t createdAt;
	int nonce; // needed for PoW

	inline void copyHashes(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash);
	inline void copyPrevious(uint8_t* sPreviousHash);
	inline void copyMerkle(uint8_t* sMerkleRootHash);

	inline void copyHashes(const uint8_t* sPreviousHash, const uint8_t* sMerkleRootHash);
	inline void copyPrevious(const uint8_t* sPreviousHash);
	inline void copyMerkle(const uint8_t* sMerkleRootHash);

	friend std::ostream& operator<<(std::ostream& s, const Header& header);

public:
	Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt);
	Header(int sVersion, const uint8_t* sPreviousHash, const uint8_t* sMerkleRootHash, uint64_t sCreatedAt);

	Header(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash);

	Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt);

	Header(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash);

	~Header();


	uint8_t* getPreviousHash();

	uint8_t* getMerkleRootHash();
};

#endif