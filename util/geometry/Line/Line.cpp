#include "Line.h"

Line::Line(Vector p1, Vector p2) {
    Vector v = p2 - p1;
    a = -v.y;
    b = v.x;
    c = -a * p1.x - b * p1.y;
}

Vector Line::get_dir_vec() const {
    return Vector(-b, a);
}

Vector Line::get_norm_vec() const {
    return Vector(a, b);
}

Vector Line::get_any_point() const {
    if (is_null(b))
        return Vector(-c / a, 0);

    return Vector(0, -c / b);
}

bool Line::operator==(Line oth) {
    float k = (is_null(a) ? oth.b / b : oth.a / a);
    if (!is_equal(a * k, oth.a))
        return false;
    if (!is_equal(b * k, oth.b))
        return false;
    if (!is_equal(c * k, oth.c))
        return false;
    return true;
}

Vector Line::get_projection(Vector p) {
    Line l1 = Line(p, p + get_norm_vec());
    return get_intersection(l1).point;
}

Intersection Line::get_intersection(Line oth) {
    Line l1(*this);
    Line l2(oth);
    if (l1 == l2)
        return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, l1.get_any_point()}; //infinity
    if (is_null(l1.get_dir_vec().vec_prod(l2.get_dir_vec())))
        return {INTERSECTION_TYPE::NO_INTERSECTIONS, {0, 0}};
    float x = (l2.b * l1.c - l1.b * l2.c) / (l1.b * l2.a - l2.b * l1.a);
    float y = (l2.a * l1.c - l1.a * l2.c) / (l1.a * l2.b - l2.a * l1.b);
    return {INTERSECTION_TYPE::HAVE_INTERSECTIONS, {x, y}};
}

Vector Line::get_normal(Vector p) {
    return p - get_projection(p);
}
