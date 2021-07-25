#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

using Vec = sf::Vector2f;

const float PI = std::acos(-1.f);
const float PI_ANGL = 180;
const float eps = 1e-3;

bool is_null(float x);
bool is_greater(float a, float b);
void rotate_vec(Vec& vec, float angl);
Vec get_segments_intersection(Vec p1, Vec p2, Vec p3, Vec p4);
Vec get_lines_intersection(Vec p1, Vec p2, Vec p3, Vec p4);
float get_angle_between_vecs(Vec v1, Vec v2);
float get_vec_length(Vec vec);
Vec get_normal_vec(Vec p1, Vec p2, Vec p3);
Vec get_projection_on_line(Vec p1, Vec p2, Vec p3);