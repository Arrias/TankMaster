#include "Game.h"

void Game::addBlock(Block *a) {
	blocks.push_back(a);
}

std::vector<Block*> Game::get_objects() {
    std::vector<Block*> ret=blocks;
    for(auto el : tanks)
        ret.push_back(el);
    return ret;
}

Block* Game::get_block(int id)  {
    for(auto el : Game::blocks) {
        if(el->get_id()==id)
            return el;
    }
}

void Game::move_tank(int id) {
    MovableBlock* tank = get_tank(id);

    tank->move(tank->get_speed());
    bool is_bad_position = false;
    for(auto el : Game::blocks) {
        if (check_blocks_intersection(tank, el)) {
            is_bad_position = true;
            break;
        }
    }
    if(is_bad_position) {
        tank->move(-tank->get_speed());
    }

}

void Game::add_tank(MovableBlock* a) {
    tanks.push_back(a);
}

MovableBlock* Game::get_tank(int id) {
    for(auto el : Game::tanks) {
        if(el->get_id()==id)
            return el;
    }
}