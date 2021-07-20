#include "MovableObject.h"

MovableObject::MovableObject(Vec cords, Vec dir, float speed, size_t type_num) :
	cords(cords), dir(dir), speed(speed), angl(0.0), type_num(type_num) {}

void MovableObject::move(float dist) {
	cords += dist * dir;
}

void MovableObject::rotate(float add_angl) {
	angl += add_angl;
	rotate_vec(dir, add_angl);
}

float MovableObject::getSpeed() const {
	return speed;
}

Vec MovableObject::get_cords() {
	return cords;
}

Vec MovableObject::get_dir() {
	return dir;
}

float MovableObject::get_angl() {
	return angl;
}

