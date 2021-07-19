#include "Tank.h"

Tank::Tank(Vec cords, Vec dir, double speed) : MovableObject(cords, dir, speed) {}

Vec Tank::get_cords() {
	return cords;
}

double Tank::get_angl() {
	return angl;
}

