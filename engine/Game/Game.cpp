#include "Game.h"

void Game::addBlock(Block *a) {
	blocks.push_back(a);
}

std::vector<Block*> Game::get_objects() {
    std::vector<Block*> ret;
    for (auto i : bullets) {
        ret.push_back((Block *)i);
    }
    for (auto i : blocks) {
        ret.push_back(i);
    }
    return ret;
}

Block* Game::get_block(int id)  {
	return blocks[id];
}

void Game::addBullet(Bullet *a) {
    bullets.push_back(a);
}

void Game::move_bullets() {
    for (auto el : bullets) {
        el->move(el->get_speed());
        // TODO check if bullet hit the target
    }
}


