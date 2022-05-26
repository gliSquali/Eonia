#include "Block.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
	Block block(0, "asdasdhgasdas", "jhdhdsgfhsgdf", "nonce", std::vector<std::string>());
	std::cout << block.toString();
	return 0;
}