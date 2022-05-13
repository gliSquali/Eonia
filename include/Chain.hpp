/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

// include guards
#ifndef CHAIN_HPP
#define CHAIN_HPP

#include "Block.hpp"
#include "SHA256.hpp"
#include <string>
#include <vector>


class Chain {
private:
	std::string name;
	unsigned long nBlocks;
	std::vector<Block> blocks;


public:
	const static uint8_t emptyHash[SHA256::SIZE];
	const static uint8_t genesisMerkleRootHash[SHA256::SIZE];


	Chain(std::string sName);
	~Chain();


	std::string getName();

	// generate new genesis block
	static Block newGenesis();

	Block getLast(); // pointer?
	Block get(unsigned long index); // pointer?

	void add(Block sBlock);
};

#endif