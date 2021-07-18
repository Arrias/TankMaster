#include "movableobject.h"

MovableObject::MovableObject(Vec cords, Vec dir, double speed) :
	cords(cords), dir(dir), speed(speed), angl(0.0) {}

void MovableObject::move_forward() {
	cords += speed * dir;
}

void MovableObject::move_back() {
	cords -= speed * dir;
}

void MovableObject::rotate(double add_angl) {
	angl += add_angl;
	rotate_vec(dir, add_angl);
}
