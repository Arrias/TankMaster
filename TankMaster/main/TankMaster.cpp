#include <SFML/Graphics.hpp>
#include "../gui/GameView/GameView.h"
#include "../engine/Game/Game.h"
#include "../gui/constants.h"
#include "../gui/TextureLoader/TextureLoader.h"
#include <iostream>

using namespace sf;
using namespace std; // WTF DUDE?

int main() {
	RenderWindow window(VideoMode(WINDOW::WIDTH, WINDOW::HEIGHT), "TankMaster");

	/*TextureLoader x;
	x.load_texture("textures/tanks/1.png");

	Game a;
	a.addTank(Tank(Vec(0, 0), Vec(1, 0), TANK_CONSTS::BASE::SPEED, 1));

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		draw_game(a, window);
		window.display();
	}*/

	Game game;
	game.addTank(Tank(Vec(0, 0), Vec(0, 1), TANK_CONSTS::BASE::SPEED, 1));

	bool moveForward = false;
	bool moveRight = false;
	bool moveLeft = false;
	bool moveBack = false;
	
	auto one_tank = game.get_tank(0);

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
			one_tank->move(-one_tank->getSpeed());
		}
		if (moveForward) {
			one_tank->move(one_tank->getSpeed());
		}
		if (moveLeft) {
			one_tank->rotate(-TANK_CONSTS::BASE::ROTATION);
		}
		if (moveRight) {
			one_tank->rotate(TANK_CONSTS::BASE::ROTATION);
		}

		window.clear(Color(0, 0, 0));
		draw_game(game, window);
		window.display();
	}

	return 0;
}