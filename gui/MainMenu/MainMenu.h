//
// Created by arrias on 31.07.2021.
//
#pragma once

#include "../Window/Window.h"

struct MainMenu : public Window {
    MainMenu(Window base);

    void show() override;

private:
    void make_menu(sf::RenderWindow &window);
};

