#pragma once
#include <SFML/Graphics.hpp>
#include "../../../util/geometry_functions/geometry_functions.h"
#include "../../EntityType/EnityType.h"

class MovableObject {
protected:
	float speed;
	float angl;
	Vec cords;
	Vec dir;
	size_t type_num;
public:
	MovableObject(Vec cords, Vec dir, float speed, size_t type);

	void rotate(float add_angl);
	void move(float dist);

	float getSpeed() const;

	Vec get_cords();
	Vec get_dir();
	float get_angl();

	virtual EntityType get_type() = 0;
};