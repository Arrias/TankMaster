//
// Created by arrias on 31.07.2021.
//

#include "Window.h"

Window::Window(std::vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader) : nav(nav), texture_loader(texture_loader) {}
