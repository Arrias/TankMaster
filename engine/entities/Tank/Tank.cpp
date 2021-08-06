#include "Tank.h"
#include <utility>

Tank::Tank(MovableBlock base, float health) : MovableBlock(std::move(base)), health(health) {}

float Tank::get_health() const {
    return health;
}

sf::Packet& operator>>(sf::Packet &packet, Tank &tank) {
    packet >> (MovableBlock&)tank >> tank.health;
    return packet;
}

sf::Packet& operator<<(sf::Packet &packet, Tank &tank) {
    packet << (MovableBlock&)tank << tank.health;
    return packet;
}
