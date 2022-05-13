#include "Block.hpp"
#include "Chain.hpp"
#include "SHA256.hpp"

#include <iostream>
#include <chrono>
#include <stdint.h>
#include <vector>

int main() {
	uint8_t* hash = new uint8_t[SHA256::SIZE];
	for(short i = 0; i < SHA256::SIZE; i++) {
		hash[i] = Chain::emptyHash[i];
	};
	Chain c("bubu");
	std::cout << c.getLast();
	return 0;
};