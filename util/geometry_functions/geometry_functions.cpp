#include "geometry_functions.h"

void rotate_vec(Vec &vec, float angl) {
    float copy_x = vec.x;
    float agl_to_rad = angl * PI / PI_ANGL;

    vec.x = vec.x * cos(agl_to_rad) - vec.y * sin(agl_to_rad);
    vec.y = copy_x * sin(agl_to_rad) + vec.y * cos(agl_to_rad);
}

bool is_null(float x) {
    return (std::abs(x) < eps);
}

bool is_greater(float a, float b) {
    return ((a - b) > eps);
}

Vec get_segments_intersection(Vec p1, Vec p2, Vec p3, Vec p4) {
    if(is_greater(p1.x,p2.x))
        std::swap(p1,p2);
    if(is_greater(p3.x,p4.x))
        std::swap(p3,p4);

    if (is_greater(p3.x, p2.x))
        return Vec(-1000, -1000);
    else if (is_null(p1.x - p2.x) && is_null(p3.x - p4.x)) {
        if (is_null(p1.x - p3.x)) {
            if (!(is_greater(std::min(p3.y, p4.y), std::max(p1.y, p2.y)) ||
                  is_greater(std::min(p1.y, p2.y), std::max(p3.y, p4.y)))) {
                if (is_greater(std::min(p1.y, p2.y), std::min(p3.y, p4.y)))
                    return Vec(p1.x, std::min(p1.y, p2.y));
                else
                    return Vec(p1.x, std::min(p3.y, p4.y));
            }
        }
        return Vec(-1000, -1000);
    } else if (is_null(p1.x - p2.x) || is_null(p3.x - p4.x)) {
        if (!is_null(p1.x - p2.x)) {
            std::swap(p1, p3);
            std::swap(p2, p4);
        }

        float xi = p1.x;
        float a2 = (p3.y-p4.y)/(p3.x-p4.x);
        float b2 = p3.y-a2*p3.x;
        float yi = a2*xi+b2;
        if(!is_greater(p3.x,xi) && !is_greater(xi,p4.x) &&
            !is_greater(std::min(p1.y,p2.y),yi) && !is_greater(yi,std::max(p1.y,p2.y)))
            return Vec(xi,yi);
        return Vec(-1000,-1000);
    }
    else {
        float a1 = (p1.y - p2.y) / (p1.x - p2.x);
        float a2 = (p3.y - p4.y) / (p3.x - p4.x);
        float b1 = p1.y - a1 * p1.x;
        float b2 = p3.y - a2 * p3.x;

        if (is_null(a1 - a2)) {
            return Vec(-1000, -1000);
        }
        float xi = (b2-b1)/(a1-a2);
        float yi = a2*xi+b2;
        if(is_greater(std::max(p1.x,p3.x),xi) || is_greater(xi,std::min(p2.x,p4.x)))
            return Vec(-1000,-1000);
        return Vec(xi,yi);
    }
}

float get_vec_length(Vec vec) {
    return std::sqrt(vec.x*vec.x+vec.y*vec.y);
}

float get_angle_between_vecs(Vec v1, Vec v2) {

    float cos_val = (v1.x*v2.x+v1.y*v2.y)/ get_vec_length(v1)* get_vec_length(v2);
    float angle = PI_ANGL*std::acos(cos_val)/PI;
    if(is_greater(v1.x,0))
        angle*=-1;
    return angle;
}

Vec get_normal_vec(Vec p1, Vec p2, Vec p3) {
    if(is_null(p2.x-p3.x)) {
        if(is_greater(p1.x,p2.x))
            return Vec(1,0);
        else
            return Vec(-1,0);
    }
    else {
        float a1 = (p2.y - p3.y) / (p2.x - p3.x);
        float b1 = p2.y - a1 * p3.x;
        if(is_null(a1)) {
            if(is_greater(p1.y,p2.y))
                return Vec(0,1);
            else
                return Vec(0,-1);
        }
        else {
            float a2 = -1.0 / a1;
            float b2 = p1.y - a2 * p1.x;

            float xi = (b2 - b1) / (a1 - a2);
            float yi = a2 * xi + b2;
            return (p1 - Vec(xi,yi));
        }
    }
}