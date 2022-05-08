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
	long index;
	// The hash of the block
	uint8_t* hash = new uint8_t[SHA256::SIZE];
	// Array of transactions
	std::vector<uint8_t*> txs;
	// Number of transactions
	int nTxs;

	friend std::ostream& operator<<(std::ostream& s, const Block& block);

public:
	Block(Header sHeader, long sIndex, std::vector<uint8_t*> sTxs);
	Block(uint8_t* sPreviousHash, uint8_t* sMerkleRootHash, uint64_t sCreateAt, long sIndex, std::vector<uint8_t*> sTxs);
	~Block();

	long getIndex();
};

#endif