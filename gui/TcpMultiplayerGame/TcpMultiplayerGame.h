#pragma once

#include "../Window/Window.h"
#include <SFML/Network.hpp>
#include "../constants.h"

struct TcpMultiplayerGame : public Window {
    explicit TcpMultiplayerGame(Window base);

    void show() override;

private:
    sf::TcpSocket socket;
};


