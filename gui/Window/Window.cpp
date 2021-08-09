//
// Created by arrias on 31.07.2021.
//

#include "Window.h"

void Window::show() {}

void Window::active(const std::function<void(sf::Event)> &process_event, const std::function<void()> &update, sf::Window &active_window) {
    while (active_window.isOpen()) {
        sf::Event event;
        while (active_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                active_window.close();
                pars.nav->clear();
                break;
            }
            process_event(event);
        }
        update();
    }
}

Window::Window(Window::Parameters pars) : pars(pars) {}
