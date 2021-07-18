#pragma once
#include "../MovableObject/MovableObject.h"

class Tank : public MovableObject {
public:
	Tank(Vec cords, Vec dir, double speed);

	sf::CircleShape paint();
};

