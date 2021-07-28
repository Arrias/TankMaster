#include "geometry_functions.h"
#include <iostream>

bool is_null(float x) {
    return (std::abs(x) < eps);
}

bool is_equal(float a, float b) {
    return is_null(a - b);
}

bool is_greater(float a, float b) {
    return ((a - b) > eps);
}

//градусы в радианы
float deg_to_rad(float angle) {
    return angle * PI / PI_ANGLE;
}

//радианы в градусы
float rad_to_deg(float angle) {
    return angle * PI_ANGLE / PI;
}

Line::Line(Vec p1, Vec p2) {
    Vec v = p2 - p1;
    a = -v.y;
    b = v.x;
    c = -a * p1.x -b * p1.y;
}

//возвращает вектор сонаправленный данной прямой
Vec Line::get_dir_vec() const {
    return {-b, a};
}

//возвращает вектор перпендикулярный данной прямой
Vec Line::get_norm_vec() const {
    return {a, b};
}

//возвращает какую-то точку, лежащую на данной прямой
Vec Line::get_any_point() const {
    if(b == 0)
        return {-c / a, 0};
    return {0, -c / b};
}

//возвращает прямую, на которой лежит отрезок
Line Segment::get_line() const {
    return {p1, p2};
}

//проверяет, что две прямые совпадают
bool operator==(Line a, Line b) {
    float k = (is_null(a.a) ? b.b / a.b : b.a / a.a);
    if(!is_equal(a.a * k, b.a))
        return false;
    if(!is_equal(a.b * k, b.b))
        return false;
    if(!is_equal(a.c * k, b.c))
        return false;
    return true;
}

float polar(Vec v) {
    float res = atan2(v.y, v.x);
    if(res < 0)
        res += 2 * PI;
    return res;
}

void rotate_vec(Vec &vec, float angle) {
    float x = vec.x, y = vec.y;
    angle = deg_to_rad(angle);
    vec.x = x * std::cos(angle) - y * std::sin(angle);
    vec.y = x * std::sin(angle) + y * std::cos(angle);
}

//векторное произведение
float vec_prod(Vec a, Vec b) {
    return a.x * b.y - a.y * b.x;
}

//скалярное произведение
float scalar_prod(Vec a, Vec b) {
    return a.x * b.x + a.y * b.y;
}

//проверяет, что p лежит между a и b на числовой прямой
bool is_into(float a, float b, float p) {
    return std::min(a, b) - eps <= p && p <= std::max(a, b) + eps;
}

Intersection get_segments_intersection(Segment s1, Segment s2) {
    Vec p1 = s1.p1, p2 = s1.p2, p3 = s2.p1, p4 = s2.p2;

    Vec v1 = p2 - p1, v2 = p4 - p3, v3 = p3 - p1;
    if (is_null(vec_prod(v1, v2))) {
        if(is_null(vec_prod(v1, v3))) {
            if (is_into(p3.x, p4.x, p1.x) && is_into(p3.y, p4.y, p1.y))
                return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, p1}; //infinity
            if (is_into(p3.x, p4.x, p2.x) && is_into(p3.y, p4.y, p2.y))
                return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, p2}; //infinity
            if (is_into(p1.x, p2.x, p3.x) && is_into(p1.y, p2.y, p3.y))
                return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, p3}; //infinity
            if (is_into(p1.x, p2.x, p4.x) && is_into(p1.y, p2.y, p4.y))
                return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, p4}; //infinity
        }
    } else {
        Intersection intersection = get_lines_intersection({p1, p2}, {p3, p4});
        if (is_into(p1.x, p2.x, intersection.point.x) &&
            is_into(p3.x, p4.x, intersection.point.x) &&
            is_into(p1.y, p2.y, intersection.point.y) &&
            is_into(p3.y, p4.y, intersection.point.y))
            return intersection;
    }
    return {INTERSECTION_TYPE::NO_INTERSECTIONS, {0, 0}};
}

Intersection get_lines_intersection(Line l1, Line l2) {
    if(l1 == l2)
        return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, l1.get_any_point()}; //infinity
    if(is_null(vec_prod(l1.get_dir_vec(), l2.get_dir_vec())))
        return {INTERSECTION_TYPE::NO_INTERSECTIONS, {0, 0}};
    float x = (l2.b * l1.c - l1.b * l2.c) / (l1.b * l2.a - l2.b * l1.a);
    float y = (l2.a * l1.c - l1.a * l2.c) / (l1.a * l2.b - l2.a * l1.b);
    return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, {x, y}};
}

float get_vec_length(Vec vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

float get_angle_between(Vec v1, Vec v2) {
    float res = polar(v1) - polar(v2);
    if(res > PI)
        res -= 2 * PI;
    else if(res < -PI)
        res += 2 * PI;
    return rad_to_deg(-res);
}

Vec get_projection_on_line(Vec p, Line l) {
    Line l1 = Line(p, p + l.get_norm_vec());
    return get_lines_intersection(l, l1).point;
}

Vec get_normal_vec(Vec p1, Line l) {
    return (p1 - get_projection_on_line(p1, l));
}