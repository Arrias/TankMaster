#pragma once
#include "../engine/entities/Tank/Tank.h"
#include "../engine/Game/Game.h"
#include "../gui/constants.h"

/*
class TcpRoom {
public:
    explicit TcpRoom(int port);
    ~TcpRoom();
    void launch();

private:
    class Player {
    public:
        Player(int id, sf::TcpSocket &socket) : id(id), socket(socket) {}
        bool shoot = false, moveForward = false, moveRight = false, moveLeft = false, moveBack = false;
        int id;
        sf::TcpSocket &socket;
    };

    void wait_players();
    void receive();

    Game game;
    sf::TcpListener listener;
    std::vector<Player> players;
    sf::SocketSelector selector;
    sf::Mutex mutex;
};
*/

