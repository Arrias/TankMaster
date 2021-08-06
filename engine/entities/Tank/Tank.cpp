#include "Tank.h"

Tank::Tank(MovableBlock base, float health) : MovableBlock(base), health(health) {}

float Tank::get_health() const {
    return health;
}

sf::Packet& operator>>(sf::Packet &packet, Tank &tank) {
    MovableBlock base;
    float hp;
    packet >> base >> hp;
    tank = Tank(base, hp);
    return packet;
}

sf::Packet& operator<<(sf::Packet &packet, Tank &tank) {
    MovableBlock base(Block (tank.cords, tank.size, tank.id, tank.angle), tank.dir, tank.speed, tank.angle_speed);
    packet << base << tank.health;
    return packet;
}
