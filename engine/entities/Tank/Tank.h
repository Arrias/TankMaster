#pragma once
#include "../MovableBlock/MovableBlock.h"

class Tank : public MovableBlock {
    float health;
    int ammunition = 10000;
public:
    Tank(MovableBlock base, float hp);

    float get_health() const;

    int get_ammunition() const;
    void add_ammunition(int add_ammo);

	virtual EntityType get_type() override;
};

