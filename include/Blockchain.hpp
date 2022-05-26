#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <memory>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <vector>

#include "Hash.hpp"
#include "Block.hpp"

#include "json.hh"
using json = nlohmann::json;

class Blockchain {
private:
	std::vector<std::unique_ptr<Block>> blockchain;
public:
	Blockchain(bool genesis = true);

	Block getBlock(uint32_t index);
	uint32_t length();
	bool addBlock(uint32_t sIndex, std::string sPrevHash, std::string sHash, std::string sNonce, std::vector<std::string>& sMerkle);
	std::string getLastHash();
	json toJSON();
	bool replaceChain(json sChain);
};

#endif