#include "UdpGameHost.h"

const size_t floor_type = 3;

void UdpGameHost::sample_game_init(Game &game) {
    Loader<Map> map_loader;
    Game temp(*map_loader.load_item("../maps/map1.json"));
    game = temp;
}

UdpGameHost::UdpGameHost(Room room, RoomId id, Address registry_ip) : game({}), room(room), id(id), registry_ip(registry_ip) {
    sample_game_init(game);
    listener.bind(stoi(room.address.value.port));
    listener.setBlocking(false);
}

UdpGameHost::~UdpGameHost() {
    game_thread->terminate();
    listener.unbind();
}

void UdpGameHost::add_new_player(Address addr) {
    int player_id = game.get_new_id();
    Vector spawn_point = game.get_map().get_spawn_points()[players.size()];
    game.add_tank(std::make_shared<Tank>(MovableBlock(
            Block(spawn_point, Vector(TANK_CONSTS::WIDTH, TANK_CONSTS::HEIGHT), player_id,
                  0), Vector(0, 1), TANK_CONSTS::BASE::SPEED, TANK_CONSTS::BASE::ROTATION), 100.0));
    //mutex.lock();
    players.insert({player_id, addr});
    //mutex.unlock();

    room.free_places.value--;

    RegistryApi api(registry_ip);
    api.edit_room(room, id);
}

void UdpGameHost::send_game() {
    sf::Packet packet;
    packet << game;
    for (auto &player : players) {
        //mutex.lock();
        listener.send(packet, player.addr.host, stoi(player.addr.port));
        //mutex.unlock();
    }
}

void UdpGameHost::update_game(float delta_time) {
    for (auto &player : players) {
        //mutex.lock();
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
        //mutex.unlock();
    }
    game.move_bullets(delta_time);
}

void UdpGameHost::launch()  {
    game_thread = std::make_shared<sf::Thread>([this]() {
        wait_players();
        sf::Thread receiver([this]() { receive(); });
        receiver.launch();

        const int RPS = 20;
        sf::Clock clock;
        while (game.is_active()) {
            float delta_time = clock.getElapsedTime().asMilliseconds();
            if (delta_time > 1000.0 / RPS) {
                update_game(delta_time);
                send_game();
                clock.restart();
            }
        }
        receiver.terminate();
    });
    game_thread->launch();
}

void UdpGameHost::wait_players() {
    while (room.free_places.value) {
        sf::Packet packet;
        sf::IpAddress addr;
        unsigned short port;

        if (listener.receive(packet, addr, port) == sf::Socket::Status::Done) {
            if (players.find({0, {addr.toString(), std::to_string(port)}}) == players.end()) {
                add_new_player({addr.toString(), std::to_string(port)});
                send_game();
            }
        }
    }
}

void UdpGameHost::receive() {
    const int RPS = 5;
    sf::Clock clock;
    while (game.is_active()) {
        float delta_time = clock.getElapsedTime().asMilliseconds();
        if (delta_time > 1000.0 / RPS) {
            sf::Packet packet;
            sf::IpAddress addr;
            unsigned short port;
            //mutex.lock();
            if(listener.receive(packet, addr, port) == sf::Socket::Status::Done) {
                auto it = players.find({0, {addr.toString(), std::to_string(port)}});
                if(it != players.end()) {
                    Player player = *it;
                    players.erase(it);
                    packet >> player.shoot >> player.moveRight >> player.moveLeft >> player.moveBack
                           >> player.moveForward;
                    players.insert(player);
                }
            }
            //mutex.unlock();
            clock.restart();
        }
    }
}