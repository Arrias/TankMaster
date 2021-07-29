#pragma once
#include "../MovableBlock/MovableBlock.h"

class Bullet : public MovableBlock {
    int strength;

public:
    Bullet(MovableBlock base, int strength);

    EntityType get_type() override;
};
