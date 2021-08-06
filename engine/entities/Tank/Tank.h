#pragma once

#include <SFML/Network.hpp>
#include "../MovableBlock/MovableBlock.h"

class Tank : public MovableBlock {
    float health;
public:
    Tank() = default;
    Tank(MovableBlock base, float hp);

    float get_health() const;

    friend sf::Packet& operator>>(sf::Packet &packet, Tank &tank);
    friend sf::Packet& operator<<(sf::Packet &packet, Tank &tank);
};

sf::Packet& operator>>(sf::Packet &packet, Tank &tank);
sf::Packet& operator<<(sf::Packet &packet, Tank &tank);