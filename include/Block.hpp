/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

// include guards
#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <string.h>
#include <vector>
#include "Header.hpp"

using string = std::string;

class Block: public Header {
private:
// int version
// string previousHash
// time_t time

	// The index of the block
	long index;
	// The hash of the block
	string hash;
	// Number of transactions
	int NTx;
	// Vector of transactions
	std::vector<string> txs;

public:
	Block(int sVersion, string sPreviousHash, string sMerkleRoot, time_t sTime, long sIndex, string sHash, std::vector<string> sTxs);
	Block(int sVersion, string sPreviousHash, string sMerkleRoot, time_t sTime, long sIndex, std::vector<string> sTxs);
	Block(Header sHeader, long sIndex, string sHash, std::vector<string> sTxs);
	~Block();

	long getIndex();
};

#endif