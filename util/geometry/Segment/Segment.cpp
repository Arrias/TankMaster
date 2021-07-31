#include "Segment.h"

Segment::Segment(Vector p1, Vector p2) : p1(p1), p2(p2) {}

Line Segment::to_line() const {
    return Line(p1, p2);
}

Intersection Segment::get_intersection(Segment oth) {
    Segment s1(*this);
    Segment s2(oth);

    Vector p1 = s1.p1, p2 = s1.p2, p3 = s2.p1, p4 = s2.p2;
    Vector v1 = p2 - p1, v2 = p4 - p3, v3 = p3 - p1;

    if (is_null(v1.vec_prod(v2))) {
        if (is_null(v1.vec_prod(v3))) {
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
        Intersection intersection = Line(p1, p2).get_intersection(Line(p3, p4));
        if (is_into(p1.x, p2.x, intersection.point.x) &&
            is_into(p3.x, p4.x, intersection.point.x) &&
            is_into(p1.y, p2.y, intersection.point.y) &&
            is_into(p3.y, p4.y, intersection.point.y))
            return intersection;
    }
    return {INTERSECTION_TYPE::NO_INTERSECTIONS, {0, 0}};
}

bool Segment::operator==(Segment oth) {
    return p1 == oth.p1 && p2 == oth.p2;
}
