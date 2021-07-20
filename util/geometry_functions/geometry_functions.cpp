#include "geometry_functions.h"

void rotate_vec(Vec& vec, float angl) {
	float copy_x = vec.x;
	float agl_to_rad = angl * PI / PI_ANGL;

	vec.x = vec.x * cos(agl_to_rad) - vec.y * sin(agl_to_rad);
	vec.y = copy_x * sin(agl_to_rad) + vec.y * cos(agl_to_rad);
}