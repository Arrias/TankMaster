#include "Tank.h"

sf::Packet& operator>>(sf::Packet &packet, Tank &tank) {
    packet >> (MovableBlock&)tank >> tank.health;
    return packet;
}

sf::Packet& operator<<(sf::Packet &packet, Tank &tank) {
    packet << (MovableBlock&)tank << tank.health;
    return packet;
}

Tank::Tank(MovableBlock base, float health) : MovableBlock(base), health(health) {}