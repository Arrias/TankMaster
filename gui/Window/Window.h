//
// Created by arrias on 31.07.2021.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../../util/Loader/Loader.h"
#include "../../util/Address/Address.h"
#include "../../TcpGameHost/TcpGameHost.h"
#include <memory>

using std::shared_ptr;
using std::vector;

struct Window {
    struct Parameters {
        vector<shared_ptr<TcpGameHost>> *games;
        vector<shared_ptr<Window>> *nav;
        Loader<sf::Texture> *texture_loader;
        Loader<sf::Font> *font_loader;
        Address registry_ip;
    };

    Parameters pars;

    Window(Parameters pars);

    virtual void show();

    void active(const std::function<void(sf::Event e)> &process_event, const std::function<void()> &update, sf::Window &active_window);

    virtual ~Window() = default;
};


