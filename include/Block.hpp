#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <stdint.h>
#include <string>
#include <vector>

#include "json.hh"
using json = nlohmann::json;

class Block {
private:
	uint32_t index;
	std::string previousHash;
	std::string blockHash;
	std::string nonce;
	std::vector<std::string> data;
public:
	Block(uint32_t index, std::string prevHas, std::string hash, std::string nonce, std::vector<std::string> data);

	std::string getPreviousHash();
	std::string getHash();
	uint32_t getIndex();
	std::vector<std::string> getData();

	std::string toString();
	json toJSON();
};

#endif