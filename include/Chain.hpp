/*
 * Copyright (c) 2022-2022 gliSquali
 * Distributed under the
*/

// include guards
#ifndef CHAIN_HPP
#define CHAIN_HPP

#include "Block.hpp"
#include <vector>

class Chain {
private:
	std::vector<Block> chain;
public:
	Chain();
	~Chain();

	Block getGenesis();
	Block getLast(); // pointer?
	Block get(long index); // pointer?
	void add(Block sBlock);
};

#endif