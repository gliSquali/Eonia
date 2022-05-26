#ifndef HASH_HPP
#define HASH_HPP

#include <sstream>
#include <string>
#include <iomanip>

#include <openssl/sha.h>
#include <openssl/ripemd.h>

std::string sha256(const std::string data) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX* sha256;
	SHA256_Init(sha256);
	SHA256_Update(sha256, data.c_str(), data.size());
	SHA256_Final(hash, sha256);

	std::stringstream ss;
	for(unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') <<(int)hash[i];
	};
	return ss.str();
};

#endif