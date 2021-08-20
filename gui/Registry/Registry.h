//
// Created by arrias on 08.08.2021.
//

#pragma once

#include "../Window/Window.h"
#include "../../registry/Room/Room.h"
#include "../Button/Button.h"

class Registry : public Window {
    std::vector<Button> buttons;
    void draw_rooms(sf::RenderWindow &window, const std::vector<Room> &rooms);
public:
    virtual void show() override;

    Registry(Window base);
};


