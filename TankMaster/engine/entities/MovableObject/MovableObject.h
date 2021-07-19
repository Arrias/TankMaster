#pragma once
#include <SFML/Graphics.hpp>
#include "../../../util/geometry_functions/geometry_functions.h"

class MovableObject {
protected:
	double speed;
	double angl;
	Vec cords;
	Vec dir;
public:
	MovableObject(Vec cords, Vec dir, double speed);

	void rotate(double add_angl);
	void move_forward(double dist);
	void move_back(double dist);

	double getSpeed() const;
};