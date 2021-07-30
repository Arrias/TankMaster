#pragma once

#include <vector>
#include "../entities/Tank/Tank.h"
#include "../entities/Bullet/Bullet.h"

class Game {
    std::vector<Block *> blocks;
    std::vector<Tank *> tanks;
    std::vector<Bullet *> bullets;

    void safe_move(int id, float dist, Vector dir);

    void safe_rotate(int id, float add_angle);

public:
    void add_block(Block *a);

    void add_tank(Tank *a);

    void add_bullet(Bullet *a);

    const std::vector<Block *> &get_blocks() const;

    const std::vector<Tank *> get_tanks() const;

    const std::vector<Bullet *> get_bullets() const;

    void move_bullets(float lambda);

    void move_tank(int id, float dist, Vector dir);

    void rotate_tank(int id, float add_angle);

    Block *get_block(int id);

    MovableBlock *get_tank(int id);
};