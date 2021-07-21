#include "geometry_functions.h"

void rotate_vec(Vec& vec, float angl) {
	float copy_x = vec.x;
	float agl_to_rad = angl * PI / PI_ANGL;

	vec.x = vec.x * cos(agl_to_rad) - vec.y * sin(agl_to_rad);
	vec.y = copy_x * sin(agl_to_rad) + vec.y * cos(agl_to_rad);
}

bool is_null(float x) {
    return (x < eps);
}

bool is_greater(float a, float b) {
    return ((a - b) > eps);
}

Vec get_segments_intersection(Vec& p1, Vec& p2, Vec& p3, Vec& p4) {
    if(is_greater(p1.x,p2.x))
        std::swap(p1,p2);
    if(is_greater(p3.x,p4.x))
        std::swap(p3,p4);

    if(is_greater(p3.x,p2.x))
        return Vec(-1000,-1000);
    else if(is_null(p1.x-p2.x) && is_null(p3.x-p4.x)) {
        if(is_null(p1.x-p3.x)) {
            if (!(is_greater(std::min(p3.y, p4.y), std::max(p1.y, p2.y)) ||
                  is_greater(std::min(p1.y, p2.y), std::max(p3.y, p4.y))))
            {
                if(is_greater(std::min(p1.y, p2.y),std::min(p3.y, p4.y)))
                    return Vec(p1.x,std::min(p1.y, p2.y));
                else
                    return Vec(p1.x,std::min(p3.y, p4.y));
            }
        }
        return Vec(-1000,-1000);
    }
    else if(is_null(p1.x-p2.x) || is_null(p3.x-p4.x)) {
        if(!is_null(p1.x-p2.x)) {
            std::swap(p1,p3);
            std::swap(p2,p4);
        }

        float xi = p1.x;
        float a2 = (p3.y-p4.y)/(p3.x-p4.x);
        float b2 = p3.y-a2*p3.x;
        float yi = a2*xi+b2;
        if(!is_greater(p3.x,xi) && !is_greater(xi,p4.x) &&
            !is_greater(std::min(p3.y,p4.y),yi) && !is_greater(yi,std::max(p3.y,p4.y)))
            return Vec(xi,yi);
        return Vec(-1000,-1000);
    }
    else {
        float a1 = (p1.y - p2.y) / (p1.x - p2.x);
        float a2 = (p3.y - p4.y) / (p3.x - p4.x);
        float b1 = p1.y - a1 * p1.x;
        float b2 = p3.y - a2 * p3.x;

        if (is_null(a1-a2)) {
            return Vec(-1000,-1000);
        }

        float xi = (b2-b1)/(a1-a2);
        float yi = a2*xi+b2;
        if(is_greater(std::max(p1.x,p3.x),xi) || is_greater(xi,std::min(p2.x,p4.x)))
            return Vec(xi,yi);
        return Vec(-1000,-1000);
    }
}

