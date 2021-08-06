#include "TankController.h"
#include "../../constants.h"

void TankController::update(sf::Event &e) {
    if (e.type == sf::Event::KeyPressed) {
        if (e.key.code == up)
            moveUp = true;
        else if (e.key.code == down)
            moveDown = true;
        else if (e.key.code == right)
            moveRight = true;
        else if (e.key.code == left)
            moveLeft = true;
    } else if (e.type == sf::Event::KeyReleased) {
        if (e.key.code == up)
            moveUp = false;
        else if (e.key.code == down)
            moveDown = false;
        else if (e.key.code == right)
            moveRight = false;
        else if (e.key.code == left)
            moveLeft = false;
    }
}

void TankController::move(float lambda) {
    if (moveDown) {
        game->move_tank(tank->get_id(), lambda * -tank->get_speed(), tank->get_dir());
    }
    if (moveUp) {
        game->move_tank(tank->get_id(), lambda * tank->get_speed(), tank->get_dir());
    }
    if (moveLeft) {
        game->rotate_tank(tank->get_id(), lambda * -TANK_CONSTS::BASE::ROTATION);
    }
    if (moveRight) {
        game->rotate_tank(tank->get_id(), lambda * TANK_CONSTS::BASE::ROTATION);
    }
}