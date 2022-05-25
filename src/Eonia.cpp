#include "Block.hpp"
#include "client_http.hpp"
#include <iostream>
#include <string>
#include <vector>

#define USE_STANDALONE_ASIO

int main() {
	Block block(0, "asdasdhgasdas", "jhdhdsgfhsgdf", "nonce", std::vector<std::string>());
	std::cout << block.toString();
	return 0;
}