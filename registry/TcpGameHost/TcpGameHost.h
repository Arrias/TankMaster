#pragma once
#include "../../engine/entities/Tank/Tank.h"
#include "../../engine/Game/Game.h"
#include "../../gui/constants.h"
#include "../../util/Loader/Loader.h"

class TcpGameHost {
public:
    explicit TcpGameHost(int port);
    ~TcpGameHost();
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
    std::shared_ptr<sf::Thread> game_thread;
    sf::Mutex mutex;
};

