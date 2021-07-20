#include "Game.h"

void Game::addTank(Tank a) {
	tanks.push_back(a);
}

std::vector<MovableObject*> Game::get_objects() {
	std::vector<MovableObject*> ret;
	for (auto& i : tanks) ret.push_back(&i);
	return ret;
}

Tank* Game::get_tank(int id) {
	return &tanks[id];
}