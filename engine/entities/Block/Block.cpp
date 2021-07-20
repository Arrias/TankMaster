#include "Block.h"

Block::Block(Vec cords, Vec size, int id, size_t type_num) : cords(cords), size(size), id(id), type_num(type_num) {}

EntityType Block::get_type() {
    return EntityType(ENTITY_NAME::BLOCK, type_num);
}
