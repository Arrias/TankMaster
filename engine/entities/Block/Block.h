#pragma once
#include <SFML/Graphics.hpp>
#include "../../../util/geometry_functions/geometry_functions.h"
#include "../../EntityType/EntityType.h"

class Block {
protected:
    Vec cords; // (!) coordinates of the center
    Vec size; // (width, height)
    int id;
    size_t type_num; // num at textures
public:
    Block(Vec cords = Vec(), Vec size = Vec(), int id = 0, size_t type_num = 1);

    virtual EntityType get_type();
};
