#include <SFML/Network.hpp>
#include <utility>
#include "../engine/entities/Tank/Tank.h"
#include "../engine/Game/Game.h"
#include "../gui/constants.h"

const float wall_thick = 50;
const size_t floor_type = 3;
const int RPS = 60;

class Player {
public:
    Player(std::shared_ptr<Tank> tank, sf::TcpSocket &socket) : tank(std::move(tank)), socket(socket) {}
    std::shared_ptr<Tank> tank;
    sf::TcpSocket &socket;
};

int id = 0;
auto get_new_id = []() {
    return id++;
};

void sample_game_init(Game &game) {
    // Add borders

    game.add_block(shared_ptr<Block>(new Block(Vector(wall_thick / 2, (float) WINDOWS_CONSTS::SINGLE_GAME::HEIGHT / 2),
                                               Vector(wall_thick, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT), get_new_id(), 0)));
    game.add_block(shared_ptr<Block>(
            new Block(Vector(WINDOWS_CONSTS::SINGLE_GAME::WIDTH - wall_thick / 2, (float) WINDOWS_CONSTS::SINGLE_GAME::HEIGHT / 2),
                      Vector(wall_thick, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT),
                      get_new_id(), 0)));

    game.add_block(shared_ptr<Block>(new Block(Vector((float) WINDOWS_CONSTS::SINGLE_GAME::WIDTH / 2, wall_thick / 2),
                                               Vector(WINDOWS_CONSTS::SINGLE_GAME::WIDTH, wall_thick), get_new_id(), 0)));
    game.add_block(shared_ptr<Block>(
            new Block(Vector((float) WINDOWS_CONSTS::SINGLE_GAME::WIDTH / 2, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT - wall_thick / 2),
                      Vector(WINDOWS_CONSTS::SINGLE_GAME::WIDTH, wall_thick),
                      get_new_id(), 0)));

    // Add sample obstacles
    game.add_block(shared_ptr<Block>(new Block(Vector(200, 200), Vector(50, 300), get_new_id(), 35)));
    game.add_block(shared_ptr<Block>(new Block(Vector(500, 500), Vector(100, 100), get_new_id(), 45)));
    game.add_block(shared_ptr<Block>(new Block(Vector(800, 800), Vector(300, 1000), get_new_id(), 69)));
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {
    Game game;
    sample_game_init(game);
    sf::TcpListener listener;
    listener.listen(2000);
    listener.setBlocking(false);
    std::vector<Player> players;

    sf::Clock clock;
    while(true) {
        if(clock.getElapsedTime().asMilliseconds() > 1000 / RPS) {
            clock.restart();

            auto* socket = new sf::TcpSocket;

            if(listener.accept(*socket) == sf::Socket::Done) {
                socket->setBlocking(false);
                shared_ptr<Tank>tank = game.add_tank(std::shared_ptr<Tank>(new Tank(MovableBlock(Block(Vector(800, 300), Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), get_new_id(), 0), Vector(0, 1), TANK_CONSTS::BASE::SPEED, TANK_CONSTS::BASE::ROTATION), 100.0)));
                players.emplace_back(tank, *socket);
            }

            for(auto &player : players) {
                sf::Packet packet;
                if(player.socket.receive(packet) == sf::Socket::Done) {
                    bool moveForward = false, moveRight = false, moveLeft = false, moveBack = false;
                    packet >> moveRight >> moveLeft >> moveBack >> moveForward;

                    if (moveBack)
                        game.move_tank(player.tank->get_id(), -player.tank->get_speed(), player.tank->get_dir());
                    else if (moveForward)
                        game.move_tank(player.tank->get_id(), player.tank->get_speed(), player.tank->get_dir());

                    if (moveLeft)
                        game.rotate_tank(player.tank->get_id(), -TANK_CONSTS::BASE::ROTATION);
                    else if (moveRight)
                        game.rotate_tank(player.tank->get_id(), TANK_CONSTS::BASE::ROTATION);
                }
            }

            sf::Packet packet;
            packet << game;
            for(auto &player : players)
                player.socket.send(packet);
        }
    }
}
#pragma clang diagnostic pop