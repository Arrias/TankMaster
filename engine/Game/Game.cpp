#include "Game.h"

void Game::addBlock(Block *a) {
	blocks.push_back(a);
}

std::vector<Block*> Game::get_objects() {
    return blocks;
}

Block* Game::get_block(int id)  {
	return blocks[id];
}
