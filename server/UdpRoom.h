#pragma once
#include <set>
#include "../engine/entities/Tank/Tank.h"
#include "../engine/Game/Game.h"
#include "../gui/constants.h"

class UdpRoom {
public:
    explicit UdpRoom(int port);
    ~UdpRoom();
    void launch();

private:
    class Player {
    public:
        Player(int id, sf::IpAddress addr, unsigned short port) : id(id), addr(addr), port(port) {}
        bool shoot = false, moveForward = false, moveRight = false, moveLeft = false, moveBack = false;
        int id;
        sf::IpAddress addr;
        unsigned short port;

        struct Comparator {
            bool operator()(const Player& a, const Player& b) const {
                return std::make_pair(a.addr, a.port) < std::make_pair(b.addr, b.port);
            }
        };
    };

    void wait_players();
    void receive();

    Game game;
    sf::UdpSocket listener;
    std::set<Player, Player::Comparator> players;
    //sf::Mutex mutex;
};