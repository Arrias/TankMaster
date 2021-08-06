#pragma once

#include "../../../engine/entities/Tank/Tank.h"
#include "../../../engine/Game/Game.h"

class TankController {
public:
    Tank *tank;
    Game *game;
    sf::Keyboard::Key left, right, up, down;

    TankController(Tank *tank, Game *game, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down)
    : tank(tank), game(game), left(left), right(right), up(up), down(down) {}

    bool moveUp = false;
    bool moveLeft = false;
    bool moveDown = false;
    bool moveRight = false;

    void update(sf::Event &e);
    void move(float lambda);
};