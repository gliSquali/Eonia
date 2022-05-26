#include "Block.hpp"

#include <iostream>
#include <stdint.h>
#include <vector>

#include "json.hh"
using json = nlohmann::json;

Block::Block(uint32_t sIndex, std::string sPrevHash, std::string sHash, std::string sNonce, std::vector<std::string> sData) {
	this->index = sIndex;
	this->previousHash = sPrevHash;
	this->blockHash = sHash;
	this->nonce = sNonce;
	this->data = sData;
	return;
};


uint32_t Block::getIndex() {
	return this->index;
};

std::string Block::getPreviousHash() {
	return this->previousHash;
};

std::string Block::getHash() {
	return this->blockHash;
};

std::vector<std::string> Block::getData() {
	return this->data;
};


std::string Block::toString() {
	std::string block = "Block " + std::to_string(this->index) + ' ' + this->blockHash + " previous hash " + this->previousHash + "\n-------------------------------\n";
	std::string dataString = "";
	for(uint32_t i = 0; i < this->data.size(); i++) {
		dataString += data[i] + "\n";
	};
	block += dataString;
	block += "-------------------------------\n";
	return block;
};

json Block::toJSON() {
	json j;
	j["index"] = this->index;
	j["previousHash"] = this->previousHash;
	j["hash"] = this->blockHash;
	j["nonce"] = this->nonce;
	j["data"] = this->data;
	return j;
};