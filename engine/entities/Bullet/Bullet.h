#pragma once
#include "../MovableBlock/MovableBlock.h"

class Bullet : public MovableBlock {
    int strength;

public:
    Bullet() = default;
    Bullet(MovableBlock base, int strength);
};
