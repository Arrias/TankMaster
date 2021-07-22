#include "Bullet.h"

Bullet::Bullet(MovableBlock base, int strength): MovableBlock(base), strength(strength) {}

EntityType Bullet::get_type() {
    return EntityType(ENTITY_NAME::BULLET, type_num);
}
