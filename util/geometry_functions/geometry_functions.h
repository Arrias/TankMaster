#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

using Vec = sf::Vector2f;

const float PI = std::acos(-1.f);
const float PI_ANGL = 180;
const float eps = 1e-5;

void rotate_vec(Vec& vec, float angl);
Vec get_segments_intersection(Vec& p1, Vec& p2, Vec& p3, Vec& p4);