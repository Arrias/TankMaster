#include "SFML/Network.hpp"
#include "../Room/Room.h"
#include "../../util/Address/Address.h"

#pragma once

class RegistryApi {
    Address registry_ip;
    sf::Http http;

public:
    explicit RegistryApi(Address registry_ip);
    bool create_room(const Room &room, Room::Identifier &id);
    bool edit_room(const Room &room, const Room::Identifier &id);
    std::vector<Room> get_rooms();

    std::vector<Room> rooms;
};


