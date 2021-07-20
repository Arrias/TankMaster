#pragma once
#include "../Block/Block.h"

class MovableBlock : public Block {
protected:
	float speed;
	float angle;
	Vec dir;
public:
	MovableBlock(Block base, Vec dir, float speed);

	void rotate(float add_angle);
	void move(float dist);

	float getSpeed() const;

	Vec get_cords();
	Vec get_dir();
	float get_angle();

	EntityType get_type() override;
};