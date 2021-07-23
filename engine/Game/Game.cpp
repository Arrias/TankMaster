#include "Game.h"
#include <cassert>

void Game::addBlock(Block *a) {
    blocks.push_back(a);
}

std::vector<Block *> Game::get_objects() {
    std::vector<Block *> ret = blocks;
    for (auto el : tanks)
        ret.push_back(el);
    return ret;
}

Block *Game::get_block(int id) {
    for (auto el : Game::blocks) {
        if (el->get_id() == id)
            return el;
    }
    assert(false);
}

void Game::move_tank(int id, float dist) {
    MovableBlock *tank = get_tank(id);

    tank->move(dist);
    bool is_bad_position = false;
    for (auto el : Game::blocks) {
        if (get_blocks_intersection(tank, el)!=Vec(-1000,-1000)) {
            is_bad_position = true;
            break;
        }
    }
    if (is_bad_position) {
        tank->move(-dist);
    }
}

void Game::rotate_tank(int id, float add_angl) {
    MovableBlock *tank = get_tank(id);

    tank->rotate(add_angl);
    bool is_bad_position=false;
    Vec sum_vec=Vec(0,0);
    for (auto block : Game::blocks) {
        if (get_blocks_intersection(tank, block)!=Vec(-1000,-1000)) {
            auto bad_segments = get_bad_segments(tank,block);
            for(auto &bad_segment : bad_segments)
                sum_vec += get_normal_vec(tank->get_cords(), bad_segment.first, bad_segment.second);
            is_bad_position=true;
            break;
        }
    }
    if (is_bad_position) {
        float old_angle = tank->get_angle();

        sum_vec.y *= -1;
        float fixe_angle = get_angle_between_vecs(sum_vec,Vec(0,-1));
        tank->rotate(-old_angle+fixe_angle);
        tank->move(tank->get_speed());
        tank->rotate(old_angle-fixe_angle);
    }
}

void Game::add_tank(MovableBlock *a) {
    tanks.push_back(a);
}

MovableBlock *Game::get_tank(int id) {
    for (auto el : Game::tanks) {
        if (el->get_id() == id)
            return el;
    }
    assert(false);
}