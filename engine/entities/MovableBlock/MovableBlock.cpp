#include "MovableBlock.h"

void MovableBlock::move(float dist) {
	cords += dist * dir;
}

void MovableBlock::rotate(float add_angle) {
	angle += add_angle;
	rotate_vec(dir, add_angle);
}

float MovableBlock::getSpeed() const {
	return speed;
}

Vec MovableBlock::get_cords() {
	return cords;
}

Vec MovableBlock::get_dir() {
	return dir;
}

float MovableBlock::get_angle() {
	return angle;
}

MovableBlock::MovableBlock(Block base, Vec dir, float speed) : Block(base), dir(dir), speed(speed) {}

EntityType MovableBlock::get_type() {
    return EntityType(ENTITY_NAME::MOVABLE_BLOCK, type_num);
}

