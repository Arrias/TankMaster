#pragma once

#include "../Window/Window.h"
#include <SFML/Network.hpp>
#include "../constants.h"

struct UdpMultiplayerGame : public Window {
    explicit UdpMultiplayerGame(Room room, Window base);

    void show() override;

private:
    bool reg();
    sf::UdpSocket socket;
    Room room;
};


