#include "SingleGame.h"
#include "../../gui/GameDrawer/GameDrawer.h"
#include "../SingleGame/TankController/TankController.h"
#include <chrono>
#include <memory>

const float wall_thick = 50;
const size_t floor_type = 3;
const int FPS = 60;

using namespace sf;

void sample_game_init(Game &game, GameDrawer &game_drawer) {
    int id = 0;
    auto get_new_id = [&id]() {
        return id++;
    };

    // Add tanks

    int tank_id1 = get_new_id();
    int tank_id2 = get_new_id();

    game_drawer.set_texture_num(tank_id1, 2);
    game_drawer.set_texture_num(tank_id2, 3);

    game.add_tank(std::make_shared<Tank>(
            MovableBlock(Block(Vector(500, 300), Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), tank_id1, 0), Vector(0, 1),
                         TANK_CONSTS::BASE::SPEED,
                         TANK_CONSTS::BASE::ROTATION),
            100.0));

    game.add_tank(std::make_shared<Tank>(
            MovableBlock(Block(Vector(800, 300), Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), tank_id2, 0), Vector(0, 1),
                         TANK_CONSTS::BASE::SPEED,
                         TANK_CONSTS::BASE::ROTATION),
            100.0));

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

    game.add_block(std::make_shared<Block>(Vector(wall_thick / 2, (float) WINDOWS_CONSTS::SINGLE_GAME::HEIGHT / 2),
                                               Vector(wall_thick, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT), wall_id1, 0));
    game.add_block(std::make_shared<Block>(
            Vector(WINDOWS_CONSTS::SINGLE_GAME::WIDTH - wall_thick / 2, (float) WINDOWS_CONSTS::SINGLE_GAME::HEIGHT / 2),
                      Vector(wall_thick, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT),
                      wall_id2, 0));

    game.add_block(std::make_shared<Block>(Vector((float) WINDOWS_CONSTS::SINGLE_GAME::WIDTH / 2, wall_thick / 2),
                                               Vector(WINDOWS_CONSTS::SINGLE_GAME::WIDTH, wall_thick), wall_id3, 0));
    game.add_block(std::make_shared<Block>(
            Vector((float) WINDOWS_CONSTS::SINGLE_GAME::WIDTH / 2, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT - wall_thick / 2),
                      Vector(WINDOWS_CONSTS::SINGLE_GAME::WIDTH, wall_thick),
                      wall_id4, 0));

    // Add sample obstacles
    game.add_block(std::make_shared<Block>(Vector(200, 200), Vector(50, 300), wall_id5, 35));
    game.add_block(std::make_shared<Block>(Vector(500, 500), Vector(100, 100), wall_id6, 45));
    game.add_block(std::make_shared<Block>(Vector(800, 800), Vector(300, 1000), wall_id7, 69));

    // Add bullet

    int bullet_id1 = get_new_id();
    game_drawer.set_texture_num(bullet_id1, 1);
    //    game.add_bullet(new Bullet(MovableBlock(Block(Vector(100, 100), Vector(BULLET_CONSTS::WIDTH, BULLET_CONSTS::HEIGHT),
    //                                                  bullet_id1, 0), Vector(1, 1), BULLET_CONSTS::BASE::SPEED, BULLET_CONSTS::BASE::SPEED),
    //                               5));

}

void SingleGame::active() {
    RenderWindow window(VideoMode(WINDOWS_CONSTS::SINGLE_GAME::WIDTH, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT), GAME_CONSTS::NAME);

    Game game;
    GameDrawer game_drawer(&game, floor_type, texture_loader);
    sample_game_init(game, game_drawer);

    TankController t1((Tank *) game.get_tank(0), &game, Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down);
    TankController t2((Tank *) game.get_tank(1), &game, Keyboard::A, Keyboard::D, Keyboard::W, Keyboard::S);

    sf::Clock clock;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) { // LEAVE TANKS
                window.close();
                nav->clear();
                break;
            }
            t1.update(event);
            t2.update(event);
        }

        if(clock.getElapsedTime().asMilliseconds() < 1000 / FPS)
            continue;
        float delta_time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        t1.move(delta_time);
        t2.move(delta_time);
        game.move_bullets(delta_time);

        window.clear(Color(0, 0, 0));
        game_drawer.draw_game(window);
        window.display();
    }
}

SingleGame::SingleGame(std::vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader) : Window(nav, texture_loader) {}















