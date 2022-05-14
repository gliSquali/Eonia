#include <iostream>
#include <chrono>

#include "Block.hpp"
#include "Blockchain.hpp"

int main() {
	Blockchain coin;

	TransactionData data;
	uint64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	data.amount = 1.5;
	data.sender = "Bob";
	data.receiver = "Alice";
	data.timestamp = time;

	coin.addBlock(data);

	std::cout << "Is chain valid? Idk " << std::endl << coin.isChainValid() << std::endl;


	time = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	data.amount = 1.5;
	data.sender = "Alberto";
	data.receiver = "Samuele";
	data.timestamp = time;

	coin.addBlock(data);

	std::cout << "Is chain valid again? Idk " << std::endl << coin.isChainValid() << std::endl;
	return 0;
};