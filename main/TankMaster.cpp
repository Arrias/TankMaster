#include <SFML/Graphics.hpp>
#include "../gui/GameView/GameView.h"
#include "../gui/constants.h"
#include <iostream>
#include <chrono>

using namespace sf;
using namespace std; // WTF DUDE?

const float wall_thick = 50;

int main() {
    RenderWindow window(VideoMode(WINDOW::WIDTH, WINDOW::HEIGHT), "TankMaster");

    Game game;

    game.addBlock(new Block(Vec(500, 500), Vec(100, 100), 6, 1, 45));
    game.addBlock(new Block(Vec(800, 800), Vec(300, 1000), 7, 1, 69));
    // Add one tank
    game.add_tank(new Tank(
            MovableBlock(Block(Vec(500, 300), Vec(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), 0, 3, 0), Vec(0, 1), TANK_CONSTS::BASE::SPEED),
            100.0));

    // Add borders
    game.addBlock(new Block(Vec(wall_thick / 2, (float) WINDOW::HEIGHT / 2), Vec(wall_thick, WINDOW::HEIGHT), 1, 1, 0));
    game.addBlock(
            new Block(Vec(WINDOW::WIDTH - wall_thick / 2, (float) WINDOW::HEIGHT / 2), Vec(wall_thick, WINDOW::HEIGHT),
                      2, 1, 0));

    game.addBlock(new Block(Vec((float) WINDOW::WIDTH / 2, wall_thick / 2), Vec(WINDOW::WIDTH, wall_thick), 3, 1, 0));
    game.addBlock(
            new Block(Vec((float) WINDOW::WIDTH / 2, WINDOW::HEIGHT - wall_thick / 2), Vec(WINDOW::WIDTH, wall_thick),
                      4, 1, 0));

    // Add sample
    game.addBlock(new Block(Vec(200, 200), Vec(50, 300), 5, 1, 35));

    bool moveForward = false;
    bool moveRight = false;
    bool moveLeft = false;
    bool moveBack = false;

    auto one_tank = game.get_tank(0);

    Block block(Vec(500, 500), Vec(500, 500));

    auto t1 = std::chrono::high_resolution_clock::now();

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

        auto t2 = std::chrono::high_resolution_clock::now();
        auto lambda = (t2 - t1).count() / 1e6;

        t1 = t2;
        if (moveBack) {
            game.move_tank(one_tank->get_id(), lambda * -one_tank->get_speed(), one_tank->get_dir());
        }
        if (moveForward) {
            game.move_tank(one_tank->get_id(), lambda * one_tank->get_speed(), one_tank->get_dir());
        }
        if (moveLeft) {
            game.rotate_tank(one_tank->get_id(), lambda * -TANK_CONSTS::BASE::ROTATION);
        }
        if (moveRight) {
            game.rotate_tank(one_tank->get_id(), lambda * TANK_CONSTS::BASE::ROTATION);
        }

        window.clear(Color(0, 0, 0));

        draw_game(game, window);
        window.display();
    }

    return 0;
}