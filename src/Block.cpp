#include <string>
#include <stdint.h>

#include "Block.hpp"

Block::Block(size_t sIndex, TransactionData sData, size_t sPreviousHash) {
	this->index = sIndex;
	this->data = sData;
	this->previousHash = sPreviousHash;
	this->hash = this->generateHash();
	return;
};

size_t Block::generateHash() {
	std::hash<std::string> hash1;
	std::hash<size_t> hash2;
	std::hash<size_t> finalHash;
	std::string toHash = std::to_string(this->data.amount) + this->data.receiver + this->data.sender + std::to_string(this->data.timestamp);
	return finalHash(hash1(toHash) + hash2(previousHash));
};

size_t Block::getHash() {
	return this->hash;
};

size_t Block::getPreviousHash() {
	return this->previousHash;
};

bool Block::isHashValid() {
	return generateHash() == this->hash;
};