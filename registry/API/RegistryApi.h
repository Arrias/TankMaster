//
// Created by arrias on 09.08.2021.
//
#include "SFML/Network.hpp"
#include "../Room/Room.h"
#include "../../util/IpAddress/IpAddress.h"

#pragma once

class RegistryApi {
    IpAddress registry_ip;
    sf::Http http;

public:
    RegistryApi(IpAddress registry_ip);
    bool create_room(const Room &room);
    std::vector<Room> get_rooms();

    std::vector<Room> rooms;
};


