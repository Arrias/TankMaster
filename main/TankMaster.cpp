#include <SFML/Graphics.hpp>
#include "../gui/GameView/GameView.h"
#include "../gui/constants.h"
#include <iostream>

using namespace sf;
using namespace std; // WTF DUDE?

const float wall_thick = 50;

int main() {
    RenderWindow window(VideoMode(WINDOW::WIDTH, WINDOW::HEIGHT), "TankMaster");

    Game game;

    // Add one tank
    game.addBlock(new Tank(
            MovableBlock(Block(Vec(500, 500), Vec(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), 1, 3), Vec(0, 1), TANK_CONSTS::BASE::SPEED),
            100.0));

    // Add borders
    game.addBlock(new Block(Vec(wall_thick / 2, (float) WINDOW::HEIGHT / 2), Vec(wall_thick, WINDOW::HEIGHT), 1, 1, 0));
    game.addBlock(
            new Block(Vec(WINDOW::WIDTH - wall_thick / 2, (float) WINDOW::HEIGHT / 2), Vec(wall_thick, WINDOW::HEIGHT),
                      1, 1, 0));

    game.addBlock(new Block(Vec((float) WINDOW::WIDTH / 2, wall_thick / 2), Vec(WINDOW::WIDTH, wall_thick), 1, 1, 0));
    game.addBlock(
            new Block(Vec((float) WINDOW::WIDTH / 2, WINDOW::HEIGHT - wall_thick / 2), Vec(WINDOW::WIDTH, wall_thick),
                      1, 1, 0));

    // Add sample
    game.addBlock(new Block(Vec(200, 200), Vec(50, 300), 1, 1, 35));

    // Add bullet
    game.addBullet(new Bullet(MovableBlock(Block(Vec(60, 60), Vec(28, 28), 0, 1, 0), Vec(0, 1), 0.3), 5));

    bool moveForward = false;
    bool moveRight = false;
    bool moveLeft = false;
    bool moveBack = false;

    auto one_tank = game.get_block(0);

    Block block(Vec(500, 500), Vec(500, 500));

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
            } else if (event.type == Event::KeyReleased) {
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

        Tank *tank = (Tank *) one_tank;
        if (moveBack) {
            tank->move(-tank->get_speed());
        }
        if (moveForward) {
            tank->move(tank->get_speed());
        }
        if (moveLeft) {
            tank->rotate(-TANK_CONSTS::BASE::ROTATION);
        }
        if (moveRight) {
            tank->rotate(TANK_CONSTS::BASE::ROTATION);
        }

        game.move_bullets();
        window.clear(Color(0, 0, 0));

        draw_game(game, window);
        window.display();
    }

    return 0;
}