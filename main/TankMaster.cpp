#include <SFML/Graphics.hpp>
#include "../gui/GameDrawer/GameDrawer.h"
#include "../gui/constants.h"
#include <iostream>
#include <chrono>

using namespace sf;
using namespace std; // WTF DUDE?

const float wall_thick = 50;
const size_t floor_type = 3;

int global_id;

int get_new_id() {
    return global_id++;
}

// For test
struct TankController {
    Tank *tank;
    Game *game;
    sf::Keyboard::Key left, right, up, down;

    TankController(Tank *tank, Game *game, Keyboard::Key left, Keyboard::Key right, Keyboard::Key up, Keyboard::Key down) : tank(tank),
                                                                                                                            game(game),
                                                                                                                            left(left),
                                                                                                                            right(right),
                                                                                                                            up(up),
                                                                                                                            down(down) {}

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

    void move(float lambda) {
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
    GameDrawer game_drawer(&game, floor_type);

    // Add tanks

    int tank_id1 = get_new_id();
    int tank_id2 = get_new_id();

    game_drawer.set_texture_num(tank_id1, 2);
    game_drawer.set_texture_num(tank_id2, 3);

    game.add_tank(new Tank(
            MovableBlock(Block(Vector(500, 300), Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), tank_id1, 0), Vector(0, 1),
                         TANK_CONSTS::BASE::SPEED,
                         TANK_CONSTS::BASE::ROTATION),
            100.0));

    TankController t1((Tank *) game.get_tank(0), &game, Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down);

    game.add_tank(new Tank(
            MovableBlock(Block(Vector(800, 300), Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), tank_id2, 0), Vector(0, 1),
                         TANK_CONSTS::BASE::SPEED,
                         TANK_CONSTS::BASE::ROTATION),
            100.0));

    TankController t2((Tank *) game.get_tank(1), &game, Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::S);


    // Add borders
    int wall_id1 = get_new_id();
    game_drawer.set_texture_num(wall_id1, 1); // (!) ADD INITIAL VALUE TO THIS CLASS
    int wall_id2 = get_new_id();
    game_drawer.set_texture_num(wall_id2, 1);
    int wall_id3 = get_new_id();
    game_drawer.set_texture_num(wall_id3, 1);
    int wall_id4 = get_new_id();
    game_drawer.set_texture_num(wall_id4, 1);
    int wall_id5 = get_new_id();
    game_drawer.set_texture_num(wall_id5, 1);
    int wall_id6 = get_new_id();
    game_drawer.set_texture_num(wall_id6, 1);
    int wall_id7 = get_new_id();
    game_drawer.set_texture_num(wall_id7, 1);

    game.add_block(new Block(Vector(wall_thick / 2, (float) WINDOW::HEIGHT / 2), Vector(wall_thick, WINDOW::HEIGHT), wall_id1, 0));
    game.add_block(
            new Block(Vector(WINDOW::WIDTH - wall_thick / 2, (float) WINDOW::HEIGHT / 2), Vector(wall_thick, WINDOW::HEIGHT),
                      wall_id2, 0));

    game.add_block(new Block(Vector((float) WINDOW::WIDTH / 2, wall_thick / 2), Vector(WINDOW::WIDTH, wall_thick), wall_id3, 0));
    game.add_block(
            new Block(Vector((float) WINDOW::WIDTH / 2, WINDOW::HEIGHT - wall_thick / 2), Vector(WINDOW::WIDTH, wall_thick),
                      wall_id4, 0));

    // Add sample obstacles
    game.add_block(new Block(Vector(200, 200), Vector(50, 300), wall_id5, 35));
    game.add_block(new Block(Vector(500, 500), Vector(100, 100), wall_id6, 45));
    game.add_block(new Block(Vector(800, 800), Vector(300, 1000), wall_id7, 69));

    // Add bullet

    int bullet_id1 = get_new_id();
    game_drawer.set_texture_num(bullet_id1, 1);
    game.add_bullet(new Bullet(MovableBlock(Block(Vector(100, 100), Vector(BULLET_CONSTS::WIDTH, BULLET_CONSTS::HEIGHT),
                                                  bullet_id1, 0), Vector(1, 1), BULLET_CONSTS::BASE::SPEED, BULLET_CONSTS::BASE::SPEED),
                               5));


    auto global_time = std::chrono::high_resolution_clock().now();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            t1.update(event);
            t2.update(event);
        }

        auto current_time = std::chrono::high_resolution_clock().now();
        auto lambda = (current_time - global_time).count() / 1e6;
        global_time = current_time;

        t1.move(lambda);
        t2.move(lambda);
        game.move_bullets(lambda);

        window.clear(Color(0, 0, 0));
        game_drawer.draw_game(window);
        window.display();
    }

    return 0;
}