#include "MovableBlock.h"

void MovableBlock::move(float dist, Vector moveDir) {
    cords += moveDir * dist;
}

float MovableBlock::get_speed() const {
    return speed;
}

Vector MovableBlock::get_dir() {
    return dir;
}

MovableBlock::MovableBlock(Block base, Vector dir, float speed, float angle_speed) : Block(base), dir(dir), speed(speed),
                                                                                     angle_speed(angle_speed) {}

void MovableBlock::rotate(float add_angle) {
    Block::rotate(add_angle);
    dir = dir.rotate(add_angle);
}

float MovableBlock::get_angle_speed() const {
    return angle_speed;
}

