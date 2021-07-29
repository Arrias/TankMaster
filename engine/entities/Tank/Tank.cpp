#include "Tank.h"

EntityType Tank::get_type() {
	return EntityType(ENTITY_NAME::TANK, type_num);
}

Tank::Tank(MovableBlock base, float health) : MovableBlock(base), health(health) {}

float Tank::get_health() const {
    return health;
}

int Tank::get_ammunition() const {
    return ammunition;
}

void Tank::add_ammunition(int add_ammo) {
    ammunition += add_ammo;
}