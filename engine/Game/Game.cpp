#include "Game.h"
#include <cassert>
#include <iostream>
#include "../../gui/constants.h"

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
    vector<shared_ptr<Bullet>> active_bullets;
    for (auto bullet : bullets) {
        float dist = bullet->get_speed() * lambda;

        bool IS_HIT = false;
        while (is_greater(dist, eps)) {
            dist -= safe_move(bullet.get(), dist, bullet->get_dir());

            if (is_greater(dist, eps)) {
                bullet->move(dist, bullet->get_dir());

                for (auto tank : Game::tanks) {
                    if (get_blocks_intersection(bullet.get(), tank.get()).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
                        tank->health -= bullet->get_strength();
                        IS_HIT = true;
                        break;
                    }
                }
                if (IS_HIT) break;

                Vector new_dir = Vector(0, 0);
                int amount = 0;
                Line dir_line = Line(bullet->get_cords(), bullet->get_cords() + bullet->get_dir());
                for (auto block : Game::blocks) {
                    if (amount > 1)
                        break;

                    for (auto bad_seg : get_bad_segments(bullet.get(), block.get())) {
                        if (amount) {
                            ++amount;
                            break;
                        }

                        Line seg_line = bad_seg.to_line();

                        float angle1 = dir_line.get_dir_vec().angle_angle_between(seg_line.get_dir_vec());

                        float angle2 = dir_line.get_dir_vec().angle_angle_between(seg_line.get_dir_vec().rotate(180));

                        float incidence_angle = angle1;
                        if (is_greater(std::abs(angle1), std::abs(angle2)))
                            incidence_angle = angle2;

                        float rotation_angle = 90 - std::abs(incidence_angle);
                        if (is_greater(0, incidence_angle))
                            rotation_angle *= -1;
                        new_dir = bullet->get_dir().rotate(180 - rotation_angle * 2);
                        ++amount;
                    }
                }

                bullet->move(-dist, bullet->get_dir());
                if (amount > 1 || !is_greater(new_dir.len(), eps)) {
                    bullet->rotate(180);
                } else {
                    new_dir.y *= -1;
                    // Vector(0,-1).polar() = 270
                    float sfml_angle = 270 - rad_to_deg(new_dir.polar());
                    if (sfml_angle > 180)
                        sfml_angle -= 360;

                    rotate_movable_object(bullet.get(), -bullet->get_angle() + sfml_angle, bullet->get_size().y / 2,
                                          -bullet->get_angle() + sfml_angle);
                }
            }
        }
        if (!IS_HIT) {
            active_bullets.push_back(bullet);
        }
    }
    bullets = active_bullets;
}

const int ITER = 20; // bp iterations count

float Game::get_max_safe_dist_to_move(MovableBlock *block_to_move, float safe, Vector dir) {
    auto update = [&safe, &block_to_move, &dir](Block *block) {
        float lo = 0, hi = safe;

        for (int iter = 0; iter < ITER; ++iter) {
            float mid = (lo + hi) / 2;
            auto copy(*block_to_move);
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
    for (auto i : blocks) {
        if (i->get_id() != block_to_move->get_id()) {
            update(i.get());
        }
    }
    for (auto i : tanks) {
        if (i->get_id() != block_to_move->get_id()) {
            update(i.get());
        }
    }
    return safe;
}

float Game::get_max_safe_dist_to_rotate(MovableBlock *block_to_rotate, float safe) {
    auto update = [&safe, &block_to_rotate](Block *block) {
        float lo = 0, hi = safe;

        for (int iter = 0; iter < ITER; ++iter) {
            float mid = (lo + hi) / 2;
            auto copy(*block_to_rotate);
            copy.rotate(mid);
            if (get_blocks_intersection(&copy, block).type == INTERSECTION_TYPE::NO_INTERSECTIONS) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        safe = lo;
    };
    for (auto i : blocks) {
        if (i->get_id() != block_to_rotate->get_id()) {
            update(i.get());
        }
    }
    for (auto i : tanks) {
        if (i->get_id() != block_to_rotate->get_id()) {
            update(i.get());
        }
    }
    return safe;
}

void Game::move_movable_object(MovableBlock *block_to_move, float dist, Vector dir) {
    safe_move(block_to_move, dist, dir);
    block_to_move->move(eps, dir);

    float add_angle = 0;
    bool crashed = false;

    auto update = [&add_angle, &crashed, &block_to_move](Block *block) {
        if (get_blocks_intersection(block_to_move, block).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
            crashed = true;

            auto bad_seg = get_bad_segments(block_to_move, block)[0];
            float angle = (bad_seg.p2 - bad_seg.p1).angle_angle_between(block_to_move->get_dir());
            float sign = 1;

            if ((0 <= angle && angle < 90) || (angle < -90)) {
                sign *= -1;
            }

            add_angle += sign * block_to_move->get_angle_speed();
        }
    };

    for (auto block : Game::blocks) {
        update(block.get());
    }

    for (auto other_tank : Game::tanks) {
        if (other_tank->get_id() != block_to_move->get_id()) {
            update(other_tank.get());
        }
    }

    if (crashed) {
        block_to_move->move(-eps, dir);
        rotate_movable_object(block_to_move, 5 * add_angle, 2 * block_to_move->get_speed(), 2 * add_angle);
    }
}

void Game::rotate_movable_object(MovableBlock *block_to_rotate, float add_angle, float safe_dist, float safe_add_angle) {
    auto copy(*block_to_rotate);
    copy.rotate(add_angle);

    Vector add_dir(0, 0);
    bool crashed = false;

    auto update = [&crashed, &copy, &add_dir, &block_to_rotate](Block *block) {
        if (get_blocks_intersection(&copy, block).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
            crashed = true;

            auto bad_segment = get_bad_segments(&copy, block)[0];
            Vector perp = (bad_segment.to_line().get_normal(block_to_rotate->get_cords())).normalize();
            add_dir += perp;
        }
    };

    for (auto block : blocks) {
        update(block.get());
    }

    for (auto other_tank : tanks) {
        if (other_tank->get_id() != block_to_rotate->get_id()) {
            update(other_tank.get());
        }
    }

    if (!crashed) {
        block_to_rotate->rotate(add_angle);
    } else {
        safe_move(block_to_rotate, safe_dist, add_dir);
        safe_rotate(block_to_rotate, safe_add_angle);
    }
}

Tank *Game::get_tank(int id) {
    for (auto el : Game::tanks) {
        if (el->get_id() == id)
            return el.get();
    }
    assert(false);
}

float Game::safe_move(MovableBlock *block_to_move, float dist, Vector dir) {
    float safe = get_max_safe_dist_to_move(block_to_move, dist, dir);
    block_to_move->move(safe, dir);
    return safe;
}

float Game::safe_rotate(MovableBlock *block_to_rotate, float add_angle) {
    float safe = get_max_safe_dist_to_rotate(block_to_rotate, add_angle);
    block_to_rotate->rotate(safe);
    return safe;
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

void Game::shoot(Tank *tank, float bullet_strength) {
    if (tank->ammunition) {
        Vector cords = tank->get_cords(), dir = tank->get_dir();
        float dist_to_move = tank->get_size().y / 2 + BULLET_CONSTS::HEIGHT + 10 * eps;
        cords += dir * dist_to_move; // std::sqrt(dist_to_move * dist_to_move / (dir.x * dir.x + dir.y * dir.y));

        auto bullet = shared_ptr<Bullet>(new Bullet(
                MovableBlock(Block(cords, Vector(BULLET_CONSTS::WIDTH, BULLET_CONSTS::HEIGHT), 9, tank->get_angle()), dir,
                             BULLET_CONSTS::BASE::SPEED,
                             0),
                bullet_strength));
        --tank->ammunition;

        bool IS_HIT = false;
        for (auto other_tank : Game::tanks) {
            if (get_blocks_intersection(bullet.get(), other_tank.get()).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
                other_tank->health -= bullet->get_strength();
                IS_HIT = true;
                break;
            }
        }
        if (!IS_HIT) {
            bool IN_BLOCK = false;
            for (auto block : Game::blocks) {
                if (get_blocks_intersection(bullet.get(), block.get()).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
                    IN_BLOCK = true;
                    break;
                }
            }
            if (IN_BLOCK)
                tank->health -= bullet->get_strength();
            else
                add_bullet(bullet);
        }
    }
}