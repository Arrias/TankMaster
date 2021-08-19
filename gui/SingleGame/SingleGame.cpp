#include "SingleGame.h"
#include "../../gui/GameDrawer/GameDrawer.h"
#include <chrono>
#include <memory>
#include "consts.h"

const float wall_thick = 50;
const size_t floor_type = 3;

using namespace sf;

struct TankController {
    Tank *tank;
    Game *game;
    sf::Keyboard::Key left, right, up, down, fire;

    TankController(Tank *tank, Game *game, Keyboard::Key left, Keyboard::Key right, Keyboard::Key up,
                   Keyboard::Key down,
                   Keyboard::Key fire) : tank(tank),
                                         game(game),
                                         left(left),
                                         right(right),
                                         up(up),
                                         down(down),
                                         fire(fire) {}

    bool moveUp = false;
    bool moveLeft = false;
    bool moveDown = false;
    bool moveRight = false;

    void update(Event &e) {
        if (e.type == Event::KeyPressed) {
            //
            if (e.key.code == fire) {
                game->shoot(tank, 25.0);
            }
            //
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
            game->move_movable_object(tank, lambda * tank->get_speed(), tank->get_dir() * -1);
        }
        if (moveUp) {
            game->move_movable_object(tank, lambda * tank->get_speed(), tank->get_dir());
        }
        if (moveLeft) {
            game->rotate_movable_object(tank, lambda * -TANK_CONSTS::BASE::ROTATION, tank->get_speed(),
                                        lambda * -TANK_CONSTS::BASE::ROTATION / 2);
        }
        if (moveRight) {
            game->rotate_movable_object(tank, lambda * TANK_CONSTS::BASE::ROTATION, tank->get_speed(),
                                        lambda * TANK_CONSTS::BASE::ROTATION / 2);
        }
    }
};

void sample_game_init(Game &game, GameDrawer &game_drawer) {
    Loader<Map> map_loader;
    Map map = *map_loader.load_item("../maps/map1.json");
    assert(map.get_spawn_points().size() >= 2);
    Game temp(map);

    int tank_id1 = temp.get_new_id();
    int tank_id2 = tank_id1 + 1;

    game_drawer.set_texture_num(tank_id1, 2);
    game_drawer.set_texture_num(tank_id2, 3);

    temp.add_tank(std::make_shared<Tank>(
            MovableBlock(Block(map.get_spawn_points()[0], Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), tank_id1, 0),
                         Vector(0, 1),
                         TANK_CONSTS::BASE::SPEED,
                         TANK_CONSTS::BASE::ROTATION),
            100.0));

    temp.add_tank(std::make_shared<Tank>(
            MovableBlock(Block(map.get_spawn_points()[1], Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), tank_id2, 0),
                         Vector(0, 1),
                         TANK_CONSTS::BASE::SPEED,
                         TANK_CONSTS::BASE::ROTATION),
            100.0));

    for (auto &i : map.get_blocks())
        game_drawer.set_texture_num(i->get_id(), 1);
    game = temp;
}

void SingleGame::show() {
    RenderWindow window(VideoMode(SINGLE_GAME::WIDTH, SINGLE_GAME::HEIGHT), GAME_CONSTS::NAME);
    window.setFramerateLimit(FPS_LIMIT);

    Game game({});
    GameDrawer game_drawer(floor_type, pars.texture_loader);
    sample_game_init(game, game_drawer);

    int tank_id1 = game.get_tanks()[0]->get_id();
    int tank_id2 = game.get_tanks()[1]->get_id();

    TankController t1((Tank *) game.get_tank(tank_id1), &game, Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down,
                      Keyboard::G);
    TankController t2((Tank *) game.get_tank(tank_id2), &game, Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::S,
                      Keyboard::F);

    sf::Clock clock;

    active([&t1, &t2](sf::Event event) {
        t1.update(event);
        t2.update(event);
    }, [&clock, &window, &t1, &t2, &game_drawer, &game]() {
        float lambda = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        t1.move(lambda);
        t2.move(lambda);

        window.clear(Color(0, 0, 0));
        game_drawer.draw_game(game, window);
        window.display();

        game.move_bullets(lambda);
    }, window);
}

SingleGame::SingleGame(Window base) : Window(base) {}














