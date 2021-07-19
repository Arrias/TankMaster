#pragma once
#include <vector>
#include "../entities/Tank/Tank.h"

class Game {
	std::vector<Tank> tanks;

public:
	void addTank(Tank a);

	std::vector<MovableObject*> get_objects();

	Tank* get_tank(int id);
};