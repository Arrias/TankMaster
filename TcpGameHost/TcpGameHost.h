#pragma once
#include "../engine/entities/Tank/Tank.h"
#include "../engine/Game/Game.h"
#include "../gui/constants.h"
#include "../util/Loader/Loader.h"
#include "../registry/Room/Room.h"
#include "../registry/API/RegistryApi.h"

typedef Room::Identifier RoomId;

class TcpGameHost {
public:
    explicit TcpGameHost(Room room, RoomId id, Address registry_ip);
    ~TcpGameHost();
    void launch();
    void add_new_player(sf::TcpSocket &socket);

private:
    class Player {
    public:
        Player(int id, sf::TcpSocket &socket) : id(id), socket(socket) {}
        bool shoot = false, moveForward = false, moveRight = false, moveLeft = false, moveBack = false;
        int id;
        sf::TcpSocket &socket;
    };

    void update_game(float delta_time);
    void send_game();
    void wait_players();
    void receive();

    Room room;
    RoomId id;
    Game game;
    Address registry_ip;
    sf::TcpListener listener;
    std::vector<Player> players;
    sf::SocketSelector selector;
    std::shared_ptr<sf::Thread> game_thread;
    sf::Mutex mutex;
};

