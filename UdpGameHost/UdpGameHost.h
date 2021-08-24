#pragma once
#include <set>
#include "../engine/entities/Tank/Tank.h"
#include "../engine/Game/Game.h"
#include "../gui/constants.h"
#include "../util/Loader/Loader.h"
#include "../registry/Room/Room.h"
#include "../registry/API/RegistryApi.h"

typedef Room::Identifier RoomId;

class UdpGameHost {
public:
    UdpGameHost(Room room, RoomId id, Address registry_ip);
    ~UdpGameHost();
    void launch();
    void add_new_player(Address addr);

private:
    class Player {
    public:
        Player(int id, Address addr) : id(id), addr(addr) {}
        bool shoot = false, moveForward = false, moveRight = false, moveLeft = false, moveBack = false;
        int id;
        Address addr;

        struct Comparator {
            bool operator()(const Player& a, const Player& b) const {
                return a.addr.getAddress() < b.addr.getAddress();
            }
        };
    };

    void sample_game_init(Game &game);
    void send_game();
    void update_game(float delta_time);
    void wait_players();
    void receive();

    Room room;
    RoomId id;
    Game game;
    Address registry_ip;
    sf::UdpSocket listener;
    std::shared_ptr<sf::Thread> game_thread;
    std::set<Player, Player::Comparator> players;
    //sf::Mutex mutex;
};