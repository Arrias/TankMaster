#pragma once
#include <vector>
#include "../entities/Tank/Tank.h"
#include "../../util/geometry_functions/geometry_functions.h"

class Game {
	std::vector<Block*> blocks;
    std::vector<MovableBlock*> tanks;

public:
	void addBlock(Block* a);
    void add_tank(MovableBlock* a);

    void move_tank(int id, float dist);
    void rotate_tank(int id, float add_angl);
	std::vector<Block*> get_objects();

	Block* get_block(int id);
    MovableBlock* get_tank(int id);
};