#pragma once
#include "../Block/Block.h"

class MovableBlock : public Block {
protected:
	float speed;
	float angle;
	Vec dir;
public:
	MovableBlock(Block base, Vec dir, float speed);

	void move(float dist);

	float get_speed() const;

	Vec get_dir();

	EntityType get_type() override;

	void rotate(float add_angle) override;
};