#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

using Vec = sf::Vector2f;

const float PI = acos(-1.f);
const float PI_ANGL = 180;

void rotate_vec(Vec& vec, float angl);
