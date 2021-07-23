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
        if (check_blocks_intersection(tank, el)) {
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
    bool is_bad_position = false;
    for (auto el : Game::blocks) {
        if (check_blocks_intersection(tank, el)) {
            is_bad_position = true;
            break;
        }
    }
    if (is_bad_position) {
        tank->rotate(-add_angl);
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