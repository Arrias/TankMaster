#pragma once

#include <vector>
#include "../entities/Tank/Tank.h"
#include "../entities/Bullet/Bullet.h"
#include "../entities/Booster/Booster.h"
#include <memory>

using std::shared_ptr;
using std::vector;

class Game {
    vector<shared_ptr<Block>> blocks;
    vector<shared_ptr<Booster>> boosters;
    vector<shared_ptr<Tank>> tanks;
    vector<shared_ptr<Bullet>> bullets;

    float get_max_safe_dist_to_move(MovableBlock *block_to_move, float safe, Vector dir);

    float get_max_safe_dist_to_rotate(MovableBlock *block_to_move, float safe);

    float safe_move(MovableBlock *block_to_move, float dist, Vector dir);

    float safe_rotate(MovableBlock *block_to_rotate, float add_angle);

public:
    void add_block(shared_ptr<Block> a);

    void add_tank(shared_ptr<Tank> a);

    void add_bullet(shared_ptr<Bullet> a);

    void add_booster(std::shared_ptr<Booster> a);

    const vector<shared_ptr<Block>> &get_blocks() const;

    const vector<shared_ptr<Tank>> get_tanks() const;

    const vector<shared_ptr<Bullet>> get_bullets() const;

    const vector<shared_ptr<Booster>> get_boosters() const;

    void move_bullets(float lambda);

    void move_movable_object(MovableBlock *block_to_move, float dist, Vector dir);

    void rotate_movable_object(MovableBlock *block_to_rotate, float add_angle, float safe_dist, float safe_add_angle);

    Block *get_block(int id);

    Tank *get_tank(int id);

    void shoot(Tank *tank, float bullet_strength);

    void update_boosters();
};