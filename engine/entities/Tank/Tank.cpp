#include "Tank.h"

Tank::Tank(MovableBlock base, float health) : MovableBlock(base), health(health) {}

float Tank::get_health() const {
    return health;
}
