#pragma once
#include <vector>
#include "../entities/Tank/Tank.h"
#include "/home/feggie/MyData/TankMaster/util/geometry_functions/geometry_functions.h"

class Game {
	std::vector<Block*> blocks;
    std::vector<MovableBlock*> tanks;

public:
	void addBlock(Block* a);
    void add_tank(MovableBlock* a);

    void move_tank(int id);
	std::vector<Block*> get_objects();

	Block* get_block(int id);
    MovableBlock* get_tank(int id);
};