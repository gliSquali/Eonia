#include <chrono>
#include <stdint.h>
#include <string>


#ifndef BLOCK_HPP
#define BLOCK_HPP

struct TransactionData {
	double amount;
	std::string sender;
	std::string receiver;
	uint64_t timestamp;
};

class Block {
private:
	size_t index;
	size_t hash;
	size_t previousHash;
	size_t generateHash();

public:
	TransactionData data;

	Block(size_t sIndex, TransactionData sData, size_t sPreviousHash);

	size_t getHash();
	size_t getPreviousHash();

	bool isHashValid();
};

#endif