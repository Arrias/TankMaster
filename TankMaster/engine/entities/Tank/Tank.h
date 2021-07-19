#pragma once
#include "../MovableObject/MovableObject.h"

class Tank : public MovableObject {
public:
	Tank(Vec cords, Vec dir, float speed, size_t type);

	virtual EntityType get_type() override;
};

