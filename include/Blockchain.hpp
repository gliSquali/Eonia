#include <chrono>
#include <stdint.h>
#include <string>
#include <vector>

#include "Block.hpp"

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

//#define prod

class Blockchain {
private:
	Block createGenesis();
public:
	std::vector<Block> chain;

	Blockchain();

	bool isChainValid();

	#ifndef prod
	void addBlock(TransactionData sData);
	Block* getLast();
	#endif
};

#endif