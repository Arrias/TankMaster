#pragma once
#include "../MovableBlock/MovableBlock.h"

class Tank : public MovableBlock {
    float health;
public:
    Tank(MovableBlock base, float hp);

    float get_health() const;

	virtual EntityType get_type() override;
};

