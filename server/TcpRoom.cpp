#include "TcpRoom.h"
#include "consts.h"
/*
const float wall_thick = 50;
const size_t floor_type = 3;

int id = 0;
auto get_new_id = []() {
    return id++;
};

void sample_game_init(Game &game) {
    game.add_block(std::make_shared<Block>(Vector(wall_thick / 2, (float) MULTIPLAYER_GAME::HEIGHT / 2),
                                           Vector(wall_thick, MULTIPLAYER_GAME::HEIGHT), get_new_id(), 0));
    game.add_block(std::make_shared<Block>(
            Vector(MULTIPLAYER_GAME::WIDTH - wall_thick / 2,
                   (float) MULTIPLAYER_GAME::HEIGHT / 2),
            Vector(wall_thick, MULTIPLAYER_GAME::HEIGHT),
            get_new_id(), 0));
    game.add_block(std::make_shared<Block>(Vector((float) MULTIPLAYER_GAME::WIDTH / 2, wall_thick / 2),
                                           Vector(MULTIPLAYER_GAME::WIDTH, wall_thick), get_new_id(), 0));
    game.add_block(std::make_shared<Block>(
            Vector((float) MULTIPLAYER_GAME::WIDTH / 2,
                   MULTIPLAYER_GAME::HEIGHT - wall_thick / 2),
            Vector(MULTIPLAYER_GAME::WIDTH, wall_thick),
            get_new_id(), 0));
    game.add_block(std::make_shared<Block>(Vector(200, 200), Vector(50, 300), get_new_id(), 35));
    game.add_block(std::make_shared<Block>(Vector(500, 500), Vector(100, 100), get_new_id(), 45));
    game.add_block(std::make_shared<Block>(Vector(800, 800), Vector(300, 1000), get_new_id(), 69));
}

TcpRoom::TcpRoom(int port) : game() {
    sample_game_init(game);
    listener.listen(port);
    selector.add(listener);
}

TcpRoom::~TcpRoom() {
    for(auto &player : players)
        delete &player.socket;
    listener.close();
}

void TcpRoom::launch()  {
    wait_players();
    sf::Thread receiver([this] () {receive();});
    receiver.launch();

    const int RPS = 30;
    sf::Clock clock;
    while (game.is_active()) {
        float delta_time = clock.getElapsedTime().asMilliseconds();
        if (delta_time > 1000.0 / RPS) {
            for (auto &player : players) {
                mutex.lock();
                if(player.shoot)
                    game.shoot(game.get_tank(player.id), 25.0);

                if (player.moveBack) {
                    game.move_movable_object(game.get_tank(player.id), delta_time * game.get_tank(player.id)->get_speed(), game.get_tank(player.id)->get_dir() * -1);
                }
                if (player.moveForward) {
                    game.move_movable_object(game.get_tank(player.id), delta_time * game.get_tank(player.id)->get_speed(), game.get_tank(player.id)->get_dir());
                }
                if (player.moveLeft) {
                    game.rotate_movable_object(game.get_tank(player.id), delta_time * -TANK_CONSTS::BASE::ROTATION, game.get_tank(player.id)->get_speed(),
                                               delta_time * -TANK_CONSTS::BASE::ROTATION / 2);
                }
                if (player.moveRight) {
                    game.rotate_movable_object(game.get_tank(player.id), delta_time * TANK_CONSTS::BASE::ROTATION, game.get_tank(player.id)->get_speed(),
                                               delta_time * TANK_CONSTS::BASE::ROTATION / 2);
                }
                mutex.unlock();
            }
            game.move_bullets(delta_time);

            sf::Packet packet;
            packet << game;
            for (auto &player : players) {
                mutex.lock();
                player.socket.send(packet);
                mutex.unlock();
            }
            clock.restart();
        }
    }
    receiver.terminate();
}

void TcpRoom::wait_players() {
    while (players.empty() && selector.wait()) {
        if (selector.isReady(listener)) {
            auto socket = new sf::TcpSocket;
            if (listener.accept(*socket) == sf::Socket::Status::Done) {
                selector.add(*socket);
                int player_id = get_new_id();
                game.add_tank(std::make_shared<Tank>(MovableBlock(
                        Block(Vector(800, 300), Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), player_id,
                              0), Vector(0, 1), TANK_CONSTS::BASE::SPEED, TANK_CONSTS::BASE::ROTATION), 100.0));
                mutex.lock();
                players.emplace_back(player_id, *socket);
                mutex.unlock();
            } else delete socket;
        }
    }
}

void TcpRoom::receive() {
    const int RPS = 20;
    sf::Clock clock;
    while (selector.wait()) {
        float delta_time = clock.getElapsedTime().asMilliseconds();
        if (delta_time > 1000.0 / RPS) {
            for (auto &player : players) {
                mutex.lock();
                sf::TcpSocket &client = player.socket;
                if (selector.isReady(client)) {
                    sf::Packet packet;
                    if (client.receive(packet) == sf::Socket::Done)
                        packet >> player.shoot >> player.moveRight >> player.moveLeft >> player.moveBack >> player.moveForward;
                }
                mutex.unlock();
            }
            clock.restart();
        }
    }
}
*/

