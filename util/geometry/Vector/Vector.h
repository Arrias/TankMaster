#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../constants.h"

struct Vector {
    float x, y;

    float len() const;

    Vector(float x = 0, float y = 0);

    Vector(sf::Vector2f vec);

    sf::Vector2f to_sfml_vector() const;

    float scalar_prod(Vector oth) const;

    float vec_prod(Vector oth) const;

    Vector normalize() const;

    float polar() const;

    float angle_angle_between(Vector oth) const;

    Vector rotate(float angle) const;

    bool operator==(Vector oth);

    Vector operator+(Vector oth);

    Vector operator*(float scalar);

    Vector operator-(Vector oth);

    void operator+=(Vector oth);

    void operator-=(Vector oth);

    void operator*=(float scalar);

    friend sf::Packet& operator>> (sf::Packet &packet, Vector &v);
    friend sf::Packet& operator<< (sf::Packet &packet, Vector &v);
};

sf::Packet& operator>> (sf::Packet &packet, Vector &v);
sf::Packet& operator<< (sf::Packet &packet, Vector &v);