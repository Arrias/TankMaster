#include "Tank.h"

Tank::Tank(Vec cords, Vec dir, double speed) : MovableObject(cords, dir, speed) {}

sf::CircleShape Tank::paint() {
	sf::CircleShape circle(50.f, 4);

	circle.setOrigin(50.f, 50.f);
	circle.setFillColor(sf::Color(230, 0, 230));
	circle.move(cords.x, cords.y);
	circle.setRotation(angl);

	return circle;
}