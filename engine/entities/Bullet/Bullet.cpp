#include "Bullet.h"

Bullet::Bullet(MovableBlock base, int strength) : MovableBlock(base), strength(strength) {}

int Bullet::get_strength() const {
    return strength;
}
