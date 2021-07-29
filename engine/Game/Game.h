#pragma once
#include <vector>
#include "../entities/Tank/Tank.h"
#include "../../util/geometry_functions/geometry_functions.h"

class Game {
	std::vector<Block*> blocks;
    std::vector<Tank*> tanks;
    std::vector<MovableBlock*> bullets;

public:
	void addBlock(Block* a);
    void add_tank(Tank* a);

    void move_tank(int id, float dist);
    void rotate_tank(int id, float add_angl);
    void shoot(int id);
    void move_all_bullets();
	std::vector<Block*> get_objects();

	Block* get_block(int id);
    Tank* get_tank(int id);
};