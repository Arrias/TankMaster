#include "Game.h"
#include <cassert>
#include <iostream>

int errors = 0;

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

void Game::addBullet(Bullet *a) {
    bullets.push_back(a);
}

void Game::move_bullets() {
    for (auto el : bullets) {
        el->move(el->get_speed());
        // TODO check if bullet hit the target
    }
}


void Game::move_tank(int id, float dist) {
    MovableBlock *tank = get_tank(id);

    tank->move(dist);
    bool is_bad_position = false;
    bool more_than_one_bad_thing = false;
    //std::pair<Vec,Vec> bad_segment;
    Vec projection_on_line, indicating_point;
    for (auto block : Game::blocks) {
        if (get_blocks_intersection(tank, block) != Vec(-1000, -1000)) {
            if (is_bad_position) {
                more_than_one_bad_thing = true;
                break;
            }

            auto bad_segments = get_bad_segments(tank, block);
            if (bad_segments.size() > 1) {
                is_bad_position = more_than_one_bad_thing = true;
                break;
            }

            //bad_segment = *bad_segments.begin();
            projection_on_line = get_projection_on_line(tank->get_cords(), bad_segments.begin()->first, bad_segments.begin()->second);
            float agl_to_rad = tank->get_angle() * PI / PI_ANGL;
            Vec dir = Vec(-std::sin(agl_to_rad), std::cos(agl_to_rad));
            indicating_point = get_lines_intersection(tank->get_cords(),
                                                      tank->get_cords() + dir,
                                                      bad_segments.begin()->first,
                                                      bad_segments.begin()->second);
            is_bad_position = true;
        }
    }
    if (is_bad_position) {
        tank->move(-dist);
    }
    if (!more_than_one_bad_thing) {
        float old_angle = tank->get_angle();

        Vec fixe_vec = indicating_point - projection_on_line;
        float deflection = std::min((float) 0.5, std::sqrt(fixe_vec.x * fixe_vec.x + fixe_vec.y * fixe_vec.y) / tank->get_size().y);

        if (!is_null(deflection)) {
            fixe_vec.y *= -1;
            float fixe_angle = get_angle_between_vecs(fixe_vec, Vec(0, -1));
            tank->rotate(-old_angle + fixe_angle);
            tank->move(std::abs(dist) * deflection);
            tank->rotate(old_angle - fixe_angle);
        }
    }
}

void Game::rotate_tank(int id, float add_angl) {
    MovableBlock *tank = get_tank(id);

    tank->rotate(add_angl);
    bool is_bad_position = false;
    bool more_than_one_bad_block = false;
    Vec sum_normal_vec = Vec(0, 0);
    for (auto block : Game::blocks) {
        if (get_blocks_intersection(tank, block) != Vec(-1000, -1000)) {
            if (is_bad_position) {
                more_than_one_bad_block = true;
                break;
            }
            auto bad_segments = get_bad_segments(tank, block);
            for (auto &bad_segment : bad_segments)
                sum_normal_vec += get_normal_vec(tank->get_cords(), bad_segment.first, bad_segment.second);
            is_bad_position = true;
        }
    }

    if (more_than_one_bad_block) {
        tank->rotate(-add_angl);
    } else if (is_bad_position) {
        float old_angle = tank->get_angle();

        sum_normal_vec.y *= -1;
        float fixe_angle = get_angle_between_vecs(sum_normal_vec, Vec(0, -1));
        tank->rotate(-old_angle + fixe_angle);
        tank->move(tank->get_speed());
        tank->rotate(old_angle - fixe_angle);
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
