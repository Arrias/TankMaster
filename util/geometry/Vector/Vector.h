
#pragma once

#include <SFML/Graphics.hpp>
#include "../constants.h"

struct Vector {
    float x, y;

    float len();

    Vector(float x = 0, float y = 0);

    Vector(sf::Vector2f vec);

    sf::Vector2f to_sfml_vector();

    float scalar_prod(Vector oth);

    float vec_prod(Vector oth);

    Vector normalize();

    float polar();

    float angle_angle_between(Vector oth);

    Vector rotate(float angle);

    bool operator==(Vector oth);

    Vector operator+(Vector oth);

    Vector operator*(float scalar);

    Vector operator-(Vector oth);

    void operator+=(Vector oth);

    void operator-=(Vector oth);

    void operator*=(float scalar);
};

