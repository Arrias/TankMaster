#pragma once

#include "../Window/Window.h"
#include <SFML/Network.hpp>
#include "../constants.h"

struct UdpMultiplayerGame : public Window {
    explicit UdpMultiplayerGame(Window base);

    void show() override;

private:
    sf::UdpSocket socket;
};


