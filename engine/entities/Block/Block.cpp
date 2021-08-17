#include "Block.h"
#include <iostream> // for debug
#include <iomanip>
#include <set>

Block::Block(Vector cords, Vector size, int id, float angle) : cords(cords), size(size), id(id),
                                                               angle(angle) {}

void Block::rotate(float add_angle) {
    angle += add_angle;
    while (angle >= 2 * PI_ANGLE) { angle -= 2 * PI_ANGLE; }
    while (angle < 0) { angle += 2 * PI_ANGLE; }
}

float Block::get_angle() const {
    return angle;
}

Vector Block::get_size() const {
    return size;
}

Vector Block::get_cords() const {
    return cords;
}

int Block::get_id() const {
    return id;
}

std::vector<Vector> get_block_points(Block *block) {
    float dx[] = {-1, 1, 1, -1};
    float dy[] = {-1, -1, 1, 1};
    std::vector<Vector> points(4);
    for (int i = 0; i < 4; ++i) {
        points[i] = {dx[i] * block->size.x / 2, dy[i] * block->size.y / 2};
        points[i] = points[i].rotate(block->get_angle());
        points[i] += block->cords;
    }
    return points; //точки идут в порядке обхода против часовой стрелки
}

bool point_in_block(Vector point, Block *block) {
    std::vector<Vector> points = get_block_points(block);
    float sum = 0;
    for (int i = 0; i < 4; ++i) {
        int nxt = (i + 1) % 4;
        Vector a = points[i] - point;
        Vector b = points[nxt] - point;
        sum += fabs(a.vec_prod(b));
    }
    return is_equal(sum, 2 * block->get_size().x * block->get_size().y);
}

Intersection get_blocks_intersection(Block *a, Block *b) {
    std::vector<Vector> points1 = get_block_points(a), points2 = get_block_points(b);
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
            Intersection intersection = segments1[i].get_intersection(segments2[j]);
            if (intersection.type == INTERSECTION_TYPE::HAVE_INTERSECTIONS)
                return intersection;
        }
    }
    return {INTERSECTION_TYPE::NO_INTERSECTIONS, {0, 0}};
}

std::vector<Segment> get_bad_segments(Block *a, Block *b) {
    std::vector<Vector> points1 = get_block_points(a), points2 = get_block_points(b);
    std::vector<Segment> segments1(4), segments2(4);

    for (int i = 0; i < 4; ++i) {
        int nxt = (i + 1) % 4;
        segments1[i] = { points1[i], points1[nxt] };
        segments2[i] = { points2[i], points2[nxt] };
    }

    std::vector<Segment> bad_segments;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (segments1[j].get_intersection(segments2[i]).type == INTERSECTION_TYPE::HAVE_INTERSECTIONS) {
                bad_segments.push_back(segments2[i]);
                break;
            }
        }
    }
    return bad_segments;
}

sf::Packet& operator>> (sf::Packet &packet, Block &block) {
    packet >> block.cords >> block.size >> block.id >> block.angle;
    return packet;
}

sf::Packet& operator<< (sf::Packet &packet, Block &block) {
    packet << block.cords << block.size << block.id << block.angle;
    return packet;
}