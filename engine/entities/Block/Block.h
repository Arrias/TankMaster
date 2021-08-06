#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../../../util/geometry/Segment/Segment.h"

class Block {
protected:
    Vector cords; // (!) coordinates of the center
    Vector size; // (width, height)
    int id;
    float angle;
public:
    Block(Vector cords = Vector(), Vector size = Vector(), int id = 0, float angle = 0);

    virtual void rotate(float add_angle);

    float get_angle() const;

    Vector get_size() const;

    Vector get_cords() const;

    int get_id() const;

    friend std::vector<Vector> get_block_points(Block *a);

    friend Intersection get_blocks_intersection(Block *a, Block *b);

    friend std::vector<Segment> get_bad_segments(Block *a, Block *b);

    friend sf::Packet& operator>> (sf::Packet &packet, Block &block);
    friend sf::Packet& operator<< (sf::Packet &packet, Block &block);
};

std::vector<Vector> get_block_points(Block *a);

Intersection get_blocks_intersection(Block *a, Block *b);

std::vector<Segment> get_bad_segments(Block *a, Block *b);

sf::Packet& operator>> (sf::Packet &packet, Block &block);
sf::Packet& operator<< (sf::Packet &packet, Block &block);