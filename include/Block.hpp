/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

// include guards
#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "SHA256.hpp"
#include "Header.hpp"
#include <ostream>
#include <vector>

class Block: public Header {
private:
// int version
// uint8_t* previousHash
// uint8_t* merkleRootHash
// uint64_t createdAt

	// The index of the block
	unsigned long index;
	// The hash of the block
	uint8_t* hash;
	// Array of transactions
	std::vector<uint8_t*> txs;
	// Number of transactions
	unsigned int nTxs;

	inline void copyHash(uint8_t* sHash);

	friend std::ostream& operator<<(std::ostream& s, const Block& block);

public:
	Block(int sVersion, uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreatedAt, unsigned long sIndex, uint8_t* sHash, std::vector<uint8_t*> sTxs);
	Block(int sVersion, const uint8_t* sPreviousHash, const uint8_t* sMerkleRootHash, uint64_t sCreatedAt, unsigned long sIndex, uint8_t* sHash, std::vector<uint8_t*> sTxs);

	Block(Header sHeader, unsigned long sIndex, uint8_t* sHash, std::vector<uint8_t*> sTxs);

	Block(Header sHeader, unsigned long sIndex, std::vector<uint8_t*> sTxs);

	Block(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, unsigned long sIndex, std::vector<uint8_t*> sTxs);
	Block(const uint8_t* sPreviousHash, const uint8_t* sMerkleRootHash, unsigned long sIndex, std::vector<uint8_t*> sTxs);

	Block(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreateAt, unsigned long sIndex, std::vector<uint8_t*> sTxs);

	~Block();


	unsigned long getIndex();
};

#endif