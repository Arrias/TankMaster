#pragma once
#include <vector>
#include "../entities/Tank/Tank.h"

class Game {
	std::vector<Block*> blocks;

public:
	void addBlock(Block* a);

	std::vector<Block*> get_objects();

	Block* get_block(int id);
};