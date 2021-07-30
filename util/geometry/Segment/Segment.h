#pragma once

#include "../Line/Line.h"

struct Segment {
    Vector p1, p2;

    Segment() = default;

    Segment(Vector p1, Vector p2);

    Line to_line() const;

    Intersection get_intersection(Segment oth);

    bool operator==(Segment oth);
};


