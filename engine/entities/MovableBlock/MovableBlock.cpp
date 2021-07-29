#include "MovableBlock.h"

void MovableBlock::move(float dist, Vec moveDir) {
    cords += dist * moveDir;
}

float MovableBlock::get_speed() const {
    return speed;
}

Vec MovableBlock::get_dir() {
    return dir;
}

MovableBlock::MovableBlock(Block base, Vec dir, float speed) : Block(base), dir(dir), speed(speed) {}

EntityType MovableBlock::get_type() {
    return EntityType(ENTITY_NAME::MOVABLE_BLOCK, type_num);
}

void MovableBlock::rotate(float add_angle) {
    Block::rotate(add_angle);
    rotate_vec(dir, add_angle);
}

