#include "Tank.h"

Tank::Tank(Vec cords, Vec dir, float speed, size_t type) : MovableObject(cords, dir, speed, type) {}

EntityType Tank::get_type() {
	return EntityType(ENTITY_NAME::TANK, type_num);
}
