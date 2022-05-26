#define USE_STANDALONE_ASIO
#define ASIO_STANDALONE 1

#include "Block.hpp"
#include "Simple-Web-Server/client_http.hpp"
#include <iostream>
#include <string>
#include <vector>


int main() {
	Block block(0, "asdasdhgasdas", "jhdhdsgfhsgdf", "nonce", std::vector<std::string>());
	std::cout << block.toString();
	return 0;
}