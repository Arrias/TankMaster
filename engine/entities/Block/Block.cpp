#include "Block.h"
#include <iostream> // for debug

Block::Block(Vec cords, Vec size, int id, size_t type_num, float angle) : cords(cords), size(size), id(id), type_num(type_num),
                                                                          angle(angle) {}

EntityType Block::get_type() {
    return EntityType(ENTITY_NAME::WALL, type_num);
}

void Block::rotate(float add_angle) {
    angle += add_angle;
}

float Block::get_angle() const {
    return angle;
}

Vec Block::get_size() {
    return size;
}

Vec Block::get_cords() {
    return cords;
}

int Block::get_id() {
    return id;
}

float dx[] = {-1, 1, 1, -1};
float dy[] = {-1, -1, 1, 1};

Vec get_blocks_intersection(Block *a, Block *b) {
    Vec cords1 = a->cords;
    Vec cords2 = b->cords;

    std::vector<Vec> points1(4, Vec(0, 0)), points2(4, Vec(0, 0));

    for (int i = 0; i < 4; ++i) {
        points1[i] = {dx[i] * a->size.x / 2, dy[i] * a->size.y / 2};
        points2[i] = {dx[i] * b->size.x / 2, dy[i] * b->size.y / 2};
    }

    std::cout << "first block" << std::endl;
    for (auto &el : points1) {
        rotate_vec(el, a->get_angle());
        el += cords1;
        std::cout << el.x << " " << el.y << std::endl;
    }

    std::cout << std::endl;
    std::cout << "second block" << std::endl;
    for (auto &el : points2) {
        rotate_vec(el, b->get_angle());
        el += cords2;
        std::cout << el.x << " " << el.y << std::endl;
    }

    for (int i = 0; i < 4; ++i) {
        Vec p1 = points1[i];
        Vec p2 = points1[(i + 1) % 4];
        for (int j = 0; j < 4; ++j) {
            Vec p3 = points2[j];
            Vec p4 = points2[(j + 1) % 4];

            Vec pnt = get_segments_intersection(p1, p2, p3, p4);
            if (pnt != Vec(-1000, -1000)) {
                return pnt;
            }
        }
    }
    return Vec(-1000, -1000);
}

std::vector<std::pair<Vec,Vec>> get_bad_segments(Block* a, Block* b) {
    Vec cords1 = a->cords;
    Vec cords2 = b->cords;

    std::vector<Vec> points1(4, Vec(0, 0)), points2(4, Vec(0, 0));

    for (int i = 0; i < 4; ++i) {
        points1[i] = {dx[i] * a->size.x / 2, dy[i] * a->size.y / 2};
        points2[i] = {dx[i] * b->size.x / 2, dy[i] * b->size.y / 2};
    }
    for (auto &el : points1) {
        rotate_vec(el, a->get_angle());
        el += cords1;
    }
    for (auto &el : points2) {
        rotate_vec(el, b->get_angle());
        el += cords2;
    }

    std::vector<std::pair<Vec,Vec>> bad_segments;
    for (int i = 0; i < 4; ++i) {
        Vec p1 = points1[i];
        Vec p2 = points1[(i + 1) % 4];
        for (int j = 0; j < 4; ++j) {
            Vec p3 = points2[j];
            Vec p4 = points2[(j + 1) % 4];

            if (get_segments_intersection(p1, p2, p3, p4) != Vec(-1000, -1000)) {
                bad_segments.emplace_back(p3, p4);
            }
        }
    }
    return bad_segments;
}