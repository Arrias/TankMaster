#pragma once

#include "../MovableBlock/MovableBlock.h"

class Tank : public MovableBlock {
public:
    float health;
    int ammunition = 10;
    Tank(MovableBlock base, float hp);
};

