#pragma once
#include "../MovableBlock/MovableBlock.h"
#include "consts.h"

class Bullet : public MovableBlock {
    int strength;

public:
    Bullet(MovableBlock base, int strength);
    int get_strength() const;
};
