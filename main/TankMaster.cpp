#include <SFML/Graphics.hpp>
#include "../gui/GameView/GameView.h"
#include "../gui/constants.h"
#include <iostream>
#include <chrono>

using namespace sf;
using namespace std; // WTF DUDE?

const float wall_thick = 50;

// For test
struct TankController {
    Tank *tank;
    Game *game;
    sf::Keyboard::Key left, right, up, down;
    std::chrono::time_point<std::chrono::high_resolution_clock> t1;

    TankController(Tank *tank, Game *game, Keyboard::Key left, Keyboard::Key right, Keyboard::Key up, Keyboard::Key down) : tank(tank),
                                                                                                                            game(game),
                                                                                                                            left(left),
                                                                                                                            right(right),
                                                                                                                            up(up),
                                                                                                                            down(down),
                                                                                                                            t1(std::chrono::high_resolution_clock::now()) {}

    bool moveUp = false;
    bool moveLeft = false;
    bool moveDown = false;
    bool moveRight = false;

    void update(Event &e) {
        if (e.type == Event::KeyPressed) {
            if (e.key.code == up) {
                moveUp = true;
            }
            if (e.key.code == down) {
                moveDown = true;
            }
            if (e.key.code == right) {
                moveRight = true;
            }
            if (e.key.code == left) {
                moveLeft = true;
            }
        } else if (e.type == Event::KeyReleased) {
            if (e.key.code == up) {
                moveUp = false;
            }
            if (e.key.code == down) {
                moveDown = false;
            }
            if (e.key.code == right) {
                moveRight = false;
            }
            if (e.key.code == left) {
                moveLeft = false;
            }
        }
    }

    void move() {
        auto cur = std::chrono::high_resolution_clock::now();
        auto lambda = (cur - t1).count() / 1e6;
        t1 = cur;

        if (moveDown) {
            game->move_tank(tank->get_id(), lambda * -tank->get_speed(), tank->get_dir());
        }
        if (moveUp) {
            game->move_tank(tank->get_id(), lambda * tank->get_speed(), tank->get_dir());
        }
        if (moveLeft) {
            game->rotate_tank(tank->get_id(), lambda * -TANK_CONSTS::BASE::ROTATION);
        }
        if (moveRight) {
            game->rotate_tank(tank->get_id(), lambda * TANK_CONSTS::BASE::ROTATION);
        }
    }
};

int main() {
    RenderWindow window(VideoMode(WINDOW::WIDTH, WINDOW::HEIGHT), "TankMaster");

    Game game;

    game.addBlock(new Block(Vec(500, 500), Vec(100, 100), 6, 1, 45));
    game.addBlock(new Block(Vec(800, 800), Vec(300, 1000), 7, 1, 69));

    // Add tanks
    game.add_tank(new Tank(
            MovableBlock(Block(Vec(500, 300), Vec(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), 0, 3, 0), Vec(0, 1), TANK_CONSTS::BASE::SPEED),
            100.0));

    TankController t1((Tank *) game.get_tank(0), &game, Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down);

    game.add_tank(new Tank(
            MovableBlock(Block(Vec(800, 300), Vec(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), 1, 2, 0), Vec(0, 1), TANK_CONSTS::BASE::SPEED),
            100.0));

    TankController t2((Tank *) game.get_tank(1), &game, Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::S);

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

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            t1.update(event);
            t2.update(event);
        }

        t1.move();
        t2.move();

        window.clear(Color(0, 0, 0));
        draw_game(game, window);
        window.display();
    }

    return 0;
}