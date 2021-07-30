#include "general_functions.h"
#include <algorithm>

bool is_null(float x) {
    return (std::abs(x) < eps);
}

bool is_equal(float a, float b) {
    return is_null(a - b);
}

bool is_into(float a, float b, float p) {
    return std::min(a, b) - eps <= p && p <= std::max(a, b) + eps;
}

bool is_greater(float a, float b) {
    return ((a - b) > eps);
}

float deg_to_rad(float angle) {
    return angle * PI / PI_ANGLE;
}

float rad_to_deg(float angle) {
    return angle * PI_ANGLE / PI;
}