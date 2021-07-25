#pragma once
#include <SFML/Graphics.hpp>
#include "../../../util/geometry_functions/geometry_functions.h"
#include "../../EntityType/EntityType.h"
#include <bitset>

class Block {
protected:
    Vec cords; // (!) coordinates of the center
    Vec size; // (width, height)
    int id;
    size_t type_num; // num at texture
    float angle;
public:
    Block(Vec cords = Vec(), Vec size = Vec(), int id = 0, size_t type_num = 1, float angle = 0);

    virtual void rotate(float add_angle);

    float get_angle() const;

    Vec get_size();

    Vec get_cords();

    int get_id();

    friend Vec get_blocks_intersection(Block *a, Block *b);

    friend std::vector<std::pair<Vec,Vec>> get_bad_segments(Block* a, Block* b);

    virtual EntityType get_type();
};

Vec get_blocks_intersection(Block* a, Block* b);
std::vector<std::pair<Vec,Vec>> get_bad_segments(Block* a, Block* b);