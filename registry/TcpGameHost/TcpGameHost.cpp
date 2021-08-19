#include "TcpGameHost.h"
#include "../consts.h"

const float wall_thick = 50;
const size_t floor_type = 3;

void sample_game_init(Game &game) {
    Loader<Map> map_loader;
    Game temp(*map_loader.load_item("../maps/map1.json"));
    game = temp;
}

TcpGameHost::TcpGameHost(int port) : game({}) {
    sample_game_init(game);
    listener.listen(port);
    selector.add(listener);
}

TcpGameHost::~TcpGameHost() {
    game_thread->terminate();
    for(auto &player : players)
        delete &player.socket;
    listener.close();
}

void TcpGameHost::launch()  {
    game_thread = std::make_shared<sf::Thread>([this]() {
        wait_players();
        sf::Thread receiver([this]() { receive(); });
        receiver.launch();

        const int RPS = 30;
        sf::Clock clock;
        while (game.is_active()) {
            float delta_time = clock.getElapsedTime().asMilliseconds();
            if (delta_time > 1000.0 / RPS) {
                for (auto &player : players) {
                    mutex.lock();
                    if (player.shoot)
                        game.shoot(game.get_tank(player.id), 25.0);

                    if (player.moveBack) {
                        game.move_movable_object(game.get_tank(player.id),
                                                 delta_time * game.get_tank(player.id)->get_speed(),
                                                 game.get_tank(player.id)->get_dir() * -1);
                    }
                    if (player.moveForward) {
                        game.move_movable_object(game.get_tank(player.id),
                                                 delta_time * game.get_tank(player.id)->get_speed(),
                                                 game.get_tank(player.id)->get_dir());
                    }
                    if (player.moveLeft) {
                        game.rotate_movable_object(game.get_tank(player.id), delta_time * -TANK_CONSTS::BASE::ROTATION,
                                                   game.get_tank(player.id)->get_speed(),
                                                   delta_time * -TANK_CONSTS::BASE::ROTATION / 2);
                    }
                    if (player.moveRight) {
                        game.rotate_movable_object(game.get_tank(player.id), delta_time * TANK_CONSTS::BASE::ROTATION,
                                                   game.get_tank(player.id)->get_speed(),
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
    });
    game_thread->launch();
}

void TcpGameHost::wait_players() {
    while (players.empty() && selector.wait()) {
        if (selector.isReady(listener)) {
            auto socket = new sf::TcpSocket;
            if (listener.accept(*socket) == sf::Socket::Status::Done) {
                selector.add(*socket);
                int player_id = game.get_new_id();
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

void TcpGameHost::receive() {
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

