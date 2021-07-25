#pragma once
#include <vector>
#include "../entities/Tank/Tank.h"
#include "../entities/Bullet/Bullet.h"

class Game {
	std::vector<Block*> blocks;
    std::vector<MovableBlock*> tanks;
	std::vector<Bullet*> bullets;

public:
	void addBlock(Block* a);
    void add_tank(MovableBlock* a);

	void addBullet(Bullet *a);

	void move_bullets();

    void move_tank(int id, float dist);
    void rotate_tank(int id, float add_angl);
	std::vector<Block*> get_objects();

	Block* get_block(int id);
    MovableBlock* get_tank(int id);
};