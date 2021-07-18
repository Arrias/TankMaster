#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

using Vec = sf::Vector2<double>;

const double PI = acos(-1);
const double PI_ANGL = 180;

void rotate_vec(Vec& vec, double angl);
