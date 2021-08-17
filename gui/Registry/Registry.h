//
// Created by arrias on 08.08.2021.
//

#pragma once

#include "../Window/Window.h"
#include "../../registry/Room/Room.h"

class Registry : public Window {

    void draw_rooms(sf::RenderWindow &window, const std::vector<Room> &rooms);
public:
    virtual void show() override;

    Registry(Window base);
};


