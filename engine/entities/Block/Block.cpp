#include "Block.h"

Block::Block(Vec cords, Vec size, int id, size_t type_num, float angle) : cords(cords), size(size), id(id), type_num(type_num),
                                                                          angle(angle) {}

EntityType Block::get_type() {
    return EntityType(ENTITY_NAME::WALL, type_num);
}

void Block::rotate(float add_angle) {
    angle += add_angle;
}

float Block::get_angle() const {
    return angle;
}

Vec Block::get_size() {
    return size;
}

Vec Block::get_cords() {
    return cords;
}
