//
// Created by arrias on 31.07.2021.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../TextureLoader/TextureLoader.h"
#include <memory>

using std::shared_ptr;
using std::vector;

struct Window {
    vector<shared_ptr<Window>> *nav;
    TextureLoader *texture_loader;

    Window(vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader);

    virtual void active() = 0;

    virtual ~Window() = default;
};


