#include "Game.h"
#include <cassert>
#include "../../gui/constants.h"
#include <iostream>

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

}

const int ITER = 10; // bp iterations count

void Game::move_tank(int id, float dist, Vec dir) {
    MovableBlock *tank = get_tank(id);
    tank->move(dist, dir);

    float add_angle = 0;
    bool crashed = false;

    for (auto block : Game::blocks) {
        if (get_blocks_intersection(tank, block).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
            crashed = true;

            auto bad_seg = get_bad_segments(tank, block)[0];
            float angle = get_angle_between(bad_seg.p2 - bad_seg.p1, tank->get_dir());
            float sign = 1;

            if ((0 <= angle && angle < 90) || (angle < -90)) {
                sign *= -1;
            }

            add_angle += sign * TANK_CONSTS::BASE::ROTATION;
        }
    }

    if (crashed) {
        tank->move(-dist, dir);
        safe_move(id, -dist / 4, dir);
        safe_rotate(id, 2 * add_angle);
        // Эти константы я подогнал (так лучше смотрится по ощущениям), тут должно быть что-то физическое
    }
}

void Game::rotate_tank(int id, float add_angle) {
    MovableBlock *tank = get_tank(id);
    auto copy(*tank);
    copy.rotate(add_angle);

    Vec add_dir(0, 0);
    bool crashed = false;

    for (auto block : Game::blocks) {
        if (get_blocks_intersection(&copy, block).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
            crashed = true;

            auto bad_segment = get_bad_segments(&copy, block)[0];
            Vec perp = normalize(get_normal_vec(tank->get_cords(), Line(bad_segment.p1, bad_segment.p2)));
            add_dir += perp;
        }
    }

    if (!crashed) {
        tank->rotate(add_angle);
    } else {
        safe_move(id, TANK_CONSTS::BASE::ROTATION, add_dir);
        safe_rotate(id, add_angle / 2);
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

void Game::safe_move(int id, float dist, Vec dir) {
    MovableBlock *tank = get_tank(id);

    float safe = dist;
    for (auto block : Game::blocks) {
        float lo = 0, hi = safe;

        for (int iter = 0; iter < ITER; ++iter) {
            float mid = (lo + hi) / 2;
            auto copy(*tank);
            copy.move(mid, dir);
            if (get_blocks_intersection(&copy, block).type == INTERSECTION_TYPE::NO_INTERSECTIONS) {
                lo = mid;
            } else {
                hi = mid;
            }
            copy.move(-mid, dir);
        }

        safe = lo;
    }

    tank->move(safe, dir);
}

void Game::safe_rotate(int id, float add_angle) {
    MovableBlock *tank = get_tank(id);

    float safe = add_angle;

    for (auto block : Game::blocks) {
        float lo = 0, hi = safe;

        for (int iter = 0; iter < ITER; ++iter) {
            float mid = (lo + hi) / 2;
            auto copy(*tank);
            copy.rotate(mid);
            if (get_blocks_intersection(&copy, block).type == INTERSECTION_TYPE::NO_INTERSECTIONS) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        safe = lo;
    }

    tank->rotate(safe);
}
