#include <SFML/Graphics.hpp>
#include <iostream>
#include "../engine/entities/Tank/Tank.h"
#include "../gui/constants.h"
#include "../gui/TextureLoader/TextureLoader.h"

using namespace sf;

TextureLoader txt;

sf::Sprite paintTank(Tank& a) {
	Sprite sprite(txt.load_texture(getPathToTexture("tank", 1)));

	sprite.setOrigin(TANK_CONSTS::BASE::ORIGIN, TANK_CONSTS::BASE::ORIGIN);
	sprite.setPosition(a.get_cords().x, a.get_cords().y);
	sprite.setRotation(a.get_angl());
	sprite.setScale(TANK_CONSTS::BASE::SCALE, TANK_CONSTS::BASE::SCALE);

	return sprite;
}

int main() {
	RenderWindow window(VideoMode(WINDOW::WIDTH, WINDOW::HEIGHT), "TankMaster");
	Tank tank = Tank(Vec(0, 0), Vec(0, 1), TANK_CONSTS::BASE::SPEED);

	bool moveForward = false;
	bool moveRight = false;
	bool moveLeft = false;
	bool moveBack = false;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Right) {
					moveRight = true;
				}
				if (event.key.code == sf::Keyboard::Left) {
					moveLeft = true;
				}
				if (event.key.code == sf::Keyboard::Up) {
					moveForward = true;
				}
				if (event.key.code == sf::Keyboard::Down) {
					moveBack = true;
				}
			}
			else if (event.type == Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Right) {
					moveRight = false;
				}
				if (event.key.code == sf::Keyboard::Left) {
					moveLeft = false;
				}
				if (event.key.code == sf::Keyboard::Up) {
					moveForward = false;
				}
				if (event.key.code == sf::Keyboard::Down) {
					moveBack = false;
				}
			}
		}

		if (moveBack) {
			tank.move_back(tank.getSpeed());
		}
		if (moveForward) {
			tank.move_forward(tank.getSpeed());
		}
		if (moveLeft) {
			tank.rotate(-TANK_CONSTS::BASE::ROTATION);
		}
		if (moveRight) {
			tank.rotate(TANK_CONSTS::BASE::ROTATION);
		}

		auto fig = paintTank(tank);
		window.clear(Color(0, 0, 0, 0));
		window.draw(fig);
		window.display();
	}


	return 0;
}