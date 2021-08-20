#pragma once

#include "../Block/Block.h"

enum class BOOSTER_TYPE {
    AMMO,
    HEALTH
};

class Booster : public Block {
public:
    BOOSTER_TYPE type;
    Booster(Block base, BOOSTER_TYPE type);
};