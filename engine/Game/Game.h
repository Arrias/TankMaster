#pragma once
#include <vector>
#include "../entities/Tank/Tank.h"
#include "../entities/Bullet/Bullet.h"

class Game {
	std::vector<Block*> blocks;
	std::vector<Bullet*> bullets;

public:
	void addBlock(Block* a);

	void addBullet(Bullet *a);

	void move_bullets();

	std::vector<Block*> get_objects();

	Block* get_block(int id);
};