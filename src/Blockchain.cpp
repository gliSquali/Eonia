#include <chrono>

#include "Blockchain.hpp"


Blockchain::Blockchain() {
	this->chain.push_back(this->createGenesis());
	return;
}

Block Blockchain::createGenesis() {
	uint64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();

	TransactionData data;
	data.amount = 0;
	data.receiver = "None";
	data.sender = "None";
	data.timestamp = time;

	std::hash<int> hash;
	return Block(0, data, hash(0));
};

#ifndef prod
//! very very bad
Block* Blockchain::getLast() {
	return &(this->chain.back());
};

void Blockchain::addBlock(TransactionData sData) {
	size_t index = this->chain.size() - 1;
	Block newBlock(index, sData, this->getLast()->getHash());
};
#endif

bool Blockchain::isChainValid() {
	std::vector<Block>::iterator it;
	size_t length = this->chain.size();

	for(it = chain.begin(); it != chain.end(); it++) {
		Block current = *it;
		if(!current.isHashValid()) {
			return false;
		};

		if(length > 1) {
			Block prev = *(it - 1);
			if(current.getPreviousHash() != prev.getHash()) {
				return false;
			};
		};

	};
	return true;
};