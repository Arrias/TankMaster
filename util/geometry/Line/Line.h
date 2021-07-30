#pragma once

#include "../Vector/Vector.h"
#include "../general_functions/general_functions.h"

enum class INTERSECTION_TYPE {
    NO_INTERSECTIONS,
    HAVE_INTERSECTIONS
};

struct Intersection {
    Intersection(INTERSECTION_TYPE type, Vector point) : type(type), point(point) {}

    INTERSECTION_TYPE type;
    Vector point;
};

struct Line {
    float a, b, c;

    Line(float a, float b, float c) : a(a), b(b), c(c) {}

    Line(Vector p1, Vector p2);

    Intersection get_intersection(Line oth);

    Vector get_dir_vec() const;

    Vector get_norm_vec() const;

    Vector get_any_point() const;

    Vector get_projection(Vector p);

    Vector get_normal(Vector p);

    bool operator==(Line oth);
};
