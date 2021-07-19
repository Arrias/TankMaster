#pragma once
#include "../MovableObject/MovableObject.h"

class Tank : public MovableObject {
public:
	Tank(Vec cords, Vec dir, double speed);

	Vec get_cords();

	double get_angl();
};

