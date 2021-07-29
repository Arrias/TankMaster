#include "Block.h"
#include <iostream> // for debug
#include <iomanip>
#include <set>

const float full_angle = 360;

Block::Block(Vec cords, Vec size, int id, size_t type_num, float angle) : cords(cords), size(size), id(id), type_num(type_num),
                                                                          angle(angle) {}

EntityType Block::get_type() {
    return {ENTITY_NAME::WALL, type_num};
}

void Block::rotate(float add_angle) {
    angle += add_angle;
    while (angle >= full_angle) angle -= full_angle;
    while (angle < 0) angle += full_angle;
}

float Block::get_angle() const {
    return angle;
}

Vec Block::get_size() const {
    return size;
}

Vec Block::get_cords() const {
    return cords;
}

int Block::get_id() const {
    return id;
}

std::vector<Vec> get_block_points(Block *block) {
    float dx[] = {-1, 1, 1, -1};
    float dy[] = {-1, -1, 1, 1};
    std::vector<Vec> points(4);
    for (int i = 0; i < 4; ++i) {
        points[i] = {dx[i] * block->size.x / 2, dy[i] * block->size.y / 2};
        rotate_vec(points[i], block->get_angle());
        points[i] += block->cords;
    }
    return points;
}

bool point_in_block(Vec point, Block *block) {
    std::vector<Vec> points = get_block_points(block);
    std::set<bool> order;
    for (int i = 0; i < 4; ++i) {
        int nxt = (i + 1) % 4;
        Vec a = points[nxt] - points[i];
        Vec b = point - points[i];
        order.insert(is_greater(vec_prod(a, b), 0));
    }
    return (order.size() == 1);
}

Intersection get_blocks_intersection(Block *a, Block *b) {
    std::vector<Vec> points1 = get_block_points(a), points2 = get_block_points(b);
    std::vector<Segment> segments1(4), segments2(4);

    for (int i = 0; i < 4; ++i) {
        int nxt = (i + 1) % 4;
        segments1[i] = {points1[i], points1[nxt]};
        segments2[i] = {points2[i], points2[nxt]};
    }
    if (point_in_block(points1[0], b))
        return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, points1[0]};
    if (point_in_block(points2[0], a))
        return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, points2[0]};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Intersection intersection = get_segments_intersection(segments1[i], segments2[j]);
            if (intersection.type == INTERSECTION_TYPE::HAVE_INTERSECTIONS)
                return intersection;
        }
    }
    return {INTERSECTION_TYPE::NO_INTERSECTIONS, {0, 0}};
}

std::vector<Segment> get_bad_segments(Block *a, Block *b) {
    std::vector<Vec> points1 = get_block_points(a), points2 = get_block_points(b);
    std::vector<Segment> segments1(4), segments2(4);

    for (int i = 0; i < 4; ++i) {
        int nxt = (i + 1) % 4;
        segments1[i] = {points1[i], points1[nxt]};
        segments2[i] = {points2[i], points2[nxt]};
    }

    std::vector<Segment> bad_segments;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (get_segments_intersection(segments1[j], segments2[i]).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
                bad_segments.push_back(segments2[i]);
                break;
            }
        }
    }
    return bad_segments;
}