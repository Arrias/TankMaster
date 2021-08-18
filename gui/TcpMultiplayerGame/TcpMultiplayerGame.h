#pragma once

#include "../Window/Window.h"
#include <SFML/Network.hpp>
#include "../constants.h"
#include "../../registry/Room/Room.h"

struct TcpMultiplayerGame : public Window {
    explicit TcpMultiplayerGame(Room room, Window base);

    void show() override;

private:
    sf::TcpSocket socket;
    Room room;
};


