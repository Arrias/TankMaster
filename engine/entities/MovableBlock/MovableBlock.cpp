#include "MovableBlock.h"
#include <utility>

void MovableBlock::move(float dist, Vector moveDir) {
    cords += moveDir * dist;
}

float MovableBlock::get_speed() const {
    return speed;
}

Vector MovableBlock::get_dir() {
    return dir;
}

MovableBlock::MovableBlock(Block base, Vector dir, float speed, float angle_speed) : Block(std::move(base)), dir(dir), speed(speed),
                                                                                     angle_speed(angle_speed) {}

void MovableBlock::rotate(float add_angle) {
    Block::rotate(add_angle);
    dir = dir.rotate(add_angle);
}

float MovableBlock::get_angle_speed() const {
    return angle_speed;
}

sf::Packet& operator>>(sf::Packet &packet, MovableBlock &block) {
    packet >> (Block&)block >> block.dir >> block.speed >> block.angle_speed;
    return packet;
}

sf::Packet& operator<<(sf::Packet &packet, MovableBlock &block) {
    packet << (Block&)block << block.dir << block.speed << block.angle_speed;
    return packet;
}