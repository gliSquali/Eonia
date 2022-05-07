#pragma once
#include <string>

struct hash {};

class Block {
private:
	std::string content;

	struct hash prev;
	struct hash hash;
public:
	Block(struct hash);
	~Block();

	void setContent(std::string);
	std::string getContent();
};

Block::Block(struct hash previous) {
}

Block::~Block() {
}

class Genesis: public Block {
public:
	Genesis();
	~Genesis();
};