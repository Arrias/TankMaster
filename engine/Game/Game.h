#pragma once

#include <memory>
#include <vector>
#include <SFML/Network.hpp>
#include "../entities/Tank/Tank.h"
#include "../entities/Bullet/Bullet.h"
#include <memory>

using std::shared_ptr;
using std::vector;

class Game {
    vector<shared_ptr<Block>> blocks;
    vector<shared_ptr<Tank>> tanks;
    vector<shared_ptr<Bullet>> bullets;

    void safe_move(int id, float dist, Vector dir);

    void safe_rotate(int id, float add_angle);

public:
    void add_block(shared_ptr<Block> a);

    shared_ptr<Tank> add_tank(shared_ptr<Tank> a);

    void add_bullet(shared_ptr<Bullet> a);

    const vector<shared_ptr<Block>> &get_blocks() const;

    const vector<shared_ptr<Tank>> get_tanks() const;

    const vector<shared_ptr<Bullet>> get_bullets() const;

    void move_bullets(float lambda);

    void move_tank(int id, float dist, Vector dir);

    void rotate_tank(int id, float add_angle);

    Block *get_block(int id);

    Tank *get_tank(int id);

    friend sf::Packet operator>>(sf::Packet &packet, Game &game);
    friend sf::Packet operator<<(sf::Packet &packet, Game &game);
};

sf::Packet operator>>(sf::Packet &packet, Game &game);
sf::Packet operator<<(sf::Packet &packet, Game &game);