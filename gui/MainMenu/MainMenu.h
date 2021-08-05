//
// Created by arrias on 31.07.2021.
//
#pragma once

#include "../Window/Window.h"

struct MainMenu : public Window {
    MainMenu(vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader);

    void active() override;

private:
    void make_menu(sf::RenderWindow &window);
};

