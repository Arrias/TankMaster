#pragma once

#include <SFML/Network.hpp>
#include "../Block/Block.h"

class MovableBlock : public Block {
protected:
    float speed;
    float angle;
    float angle_speed;
    Vector dir;
public:
    MovableBlock() = default;
    MovableBlock(Block base, Vector dir, float speed, float angle_speed);

    void move(float dist, Vector moveDir);

    float get_speed() const;

    float get_angle_speed() const;

    Vector get_dir();

    void rotate(float add_angle) override;

    friend sf::Packet& operator>>(sf::Packet &packet, MovableBlock &block);
    friend sf::Packet& operator<<(sf::Packet &packet, MovableBlock &block);
};