#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>

using Vec = sf::Vector2f;
class Line {
public:
    Line(float a, float b, float c) : a(a), b(b), c(c) {}
    Line(Vec p1, Vec p2);
    Vec get_dir_vec() const;
    Vec get_norm_vec() const;
    Vec get_any_point() const;
    float a, b, c;
};

bool operator==(Line a, Line b);

class Segment {
public:
    Segment() = default;
    Segment(Vec p1, Vec p2) : p1(p1), p2(p2) {}
    Line get_line() const;
    Vec p1, p2;
};

enum class INTERSECTION_TYPE {
    NO_INTERSECTIONS,
    HAVE_INTERSECTIONS
};

class Intersection {
public:
    Intersection (INTERSECTION_TYPE type, Vec point) : type(type), point(point) {}
    INTERSECTION_TYPE type;
    Vec point;
};

const float PI = std::acos(-1.f);
const float PI_ANGLE = 180;
const float eps = 1e-3;

bool is_null(float x);
bool is_equal(float a, float b);
bool is_greater(float a, float b);
void rotate_vec(Vec& vec, float angle);
float vec_prod(Vec a, Vec b);
float scalar_prod(Vec a, Vec b);
float deg_to_rad(float angle);
float rad_to_deg(float angle);
float polar(Vec v);
Intersection get_segments_intersection(Segment s1, Segment s2);
Intersection get_lines_intersection(Line l1, Line l2);
float get_angle_between(Vec v1, Vec v2);
float get_vec_length(Vec vec);
Vec get_projection_on_line(Vec p, Line l);
Vec get_normal_vec(Vec p1, Line l);