#include <SFML/Graphics.hpp>
#include <iostream>
#include "../engine/entities/Tank/Tank.h"

using namespace sf;

int main() {
	RenderWindow window(VideoMode(500, 500), "TankMaster");

	Tank* a = new Tank(Vec(0, 0), Vec(1, 0), 10);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.key.code == Keyboard::Down) {
				a->move_back();
			}
			else if (event.key.code == Keyboard::Up) {
				a->move_forward();
			}
			else if (event.key.code == Keyboard::Right) {
				a->rotate(5);
			}
			else if (event.key.code == Keyboard::Left) {
				a->rotate(-5);
			}
		}

		auto fig = a->paint();
		window.clear(Color(250, 220, 100, 0));
		window.draw(fig);
		//std::cout << fig.getOrigin().x << " " << fig.getOrigin().y << std::endl;

		window.display();
	}


	return 0;
}