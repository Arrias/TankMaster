#pragma once

#include "../MovableBlock/MovableBlock.h"
#include "consts.h"

class Tank : public MovableBlock {
public:
    float health;
    int ammunition = 10000;
    Tank(MovableBlock base, float hp);
};

