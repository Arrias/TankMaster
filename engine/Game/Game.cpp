#include "Game.h"
#include <cassert>
#include <iostream>

void Game::add_block(shared_ptr<Block> a) {
    blocks.push_back(a);
}

Block *Game::get_block(int id) {
    for (auto el : Game::blocks) {
        if (el->get_id() == id)
            return el.get();
    }
    assert(false);
}

void Game::add_bullet(shared_ptr<Bullet> a) {
    bullets.push_back(a);
}

void Game::move_bullets(float lambda) {
    for (auto el : bullets) {
        el->move(el->get_speed() * lambda, el->get_dir());
    }
}

const int ITER = 10; // bp iterations count

void Game::move_tank(int id, float dist, Vector dir) {
    MovableBlock *tank = get_tank(id);
    tank->move(dist, dir);

    float add_angle = 0;
    bool crashed = false;

    auto update = [&add_angle, &crashed, &tank](Block *block) {
        if (get_blocks_intersection(tank, block).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
            crashed = true;

            auto bad_seg = get_bad_segments(tank, block)[0];
            float angle = (bad_seg.p2 - bad_seg.p1).angle_angle_between(tank->get_dir());
            float sign = 1;

            if ((0 <= angle && angle < 90) || (angle < -90)) {
                sign *= -1;
            }

            add_angle += sign * tank->get_angle_speed();
        }
    };

    for (auto block : Game::blocks) {
        update(block.get());
    }

    for (auto other_tank : Game::tanks) {
        if (other_tank->get_id() != tank->get_id()) {
            update(other_tank.get());
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

    Vector add_dir(0, 0);
    bool crashed = false;

    auto update = [&crashed, &copy, &add_dir, &tank](Block *block) {
        if (get_blocks_intersection(&copy, block).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
            crashed = true;

            auto bad_segment = get_bad_segments(&copy, block)[0];
            Vector perp = (bad_segment.to_line().get_normal(tank->get_cords())).normalize();
            add_dir += perp;
        }
    };

    for (auto block : blocks) {
        update(block.get());
    }

    for (auto other_tank : tanks) {
        if (other_tank->get_id() != tank->get_id()) {
            update(other_tank.get());
        }
    }

    if (!crashed) {
        tank->rotate(add_angle);
    } else {
        safe_move(id, tank->get_speed(), add_dir);
        safe_rotate(id, add_angle / 2);
    }
}

Tank *Game::get_tank(int id) {
    for (auto el : Game::tanks) {
        if (el->get_id() == id)
            return el.get();
    }
    assert(false);
}

void Game::safe_move(int id, float dist, Vector dir) {
    MovableBlock *tank = get_tank(id);

    float safe = dist;

    auto update = [&safe, &tank, &dir](Block *block) {
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
    };

    for (auto block : blocks) {
        update(block.get());
    }

    for (auto other_tank : tanks) {
        if (other_tank->get_id() != tank->get_id()) {
            update(other_tank.get());
        }
    }

    tank->move(safe, dir);
}

void Game::safe_rotate(int id, float add_angle) {
    MovableBlock *tank = get_tank(id);

    float safe = add_angle;

    auto update = [&safe, &tank](Block *block) {
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
    };

    for (auto block : blocks) {
        update(block.get());
    }
    for (auto other_tank : tanks) {
        if (other_tank->get_id() != tank->get_id()) {
            update(other_tank.get());
        }
    }

    tank->rotate(safe);
}

const std::vector<shared_ptr<Block>> &Game::get_blocks() const {
    return blocks;
}

const std::vector<shared_ptr<Tank>> Game::get_tanks() const {
    return tanks;
}

const std::vector<shared_ptr<Bullet>> Game::get_bullets() const {
    return bullets;
}

void Game::add_tank(shared_ptr<Tank> a) {
    tanks.push_back(a);
}



