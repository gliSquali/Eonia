#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class Header {
	public:
		Header(int index, string prevHas, string hash, string nonce);
		string getPreviousHash();
		string getHash();
		int getIndex();
	protected:
		int index;
		string previousHash;
		string blockHash;
		string nonce;
};
// Constructor
Header::Header(int index, string prevHash, string hash, string nonce) {
	this->previousHash = prevHash;
	this->index = index;
	this->nonce = nonce;
	this->blockHash = hash;
};

int Header::getIndex() {
	return this->index;
};

string Header::getPreviousHash() {
	return this->previousHash;
};

string Header::getHash() {
	return this->blockHash;
};

#endif // HEADER_HPP