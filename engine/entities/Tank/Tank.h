#pragma once

#include<SFML//Network.hpp>
#include "../MovableBlock/MovableBlock.h"
#include "consts.h"

class Tank : public MovableBlock {
public:
    float health;
    int ammunition = 10000;
    Tank() = default;
    Tank(MovableBlock base, float hp);
    friend sf::Packet& operator>>(sf::Packet &packet, Tank &tank);
    friend sf::Packet& operator<<(sf::Packet &packet, Tank &tank);
};

