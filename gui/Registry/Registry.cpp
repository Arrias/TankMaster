//
// Created by arrias on 08.08.2021.
//

#include "Registry.h"
#include "../constants.h"
#include "../../registry/API/RegistryApi.h"
#include "../Button/Button.h"
#include "consts.h"
#include <iostream>

Registry::Registry(Window base) : Window(base) {}

void Registry::draw_rooms(sf::RenderWindow &window, const std::vector<Room> &rooms) {
    auto get_button_with_text = [this](string title) {
        sf::Text text;
        text.setString(title);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setFont(*pars.font_loader->load_item(path_to_font));
        text.setCharacterSize(buttons_letter_size);
        return text;
    };

    std::vector<Button> buttons;
    Vector but_size = Vector(500, 250);
    int id = 0;

    auto button_texture = pars.texture_loader->load_item("buttons", 1);
    auto active_button_texture = pars.texture_loader->load_item("buttons", 2);

    for (auto &room : rooms) {
        ++id;
        buttons.push_back(Button(Block(Vector(REGISTRY::WIDTH / 2, 250 * id), but_size, 0, 0),
                                 button_texture, active_button_texture,
                                 get_button_with_text(room.creator_name.value + " " + room.address.value.getAddress())));
    }

    for (auto &but : buttons) {
        but.draw(window);
    }
}

void Registry::show() {
    sf::RenderWindow window(sf::VideoMode(REGISTRY::WIDTH, REGISTRY::HEIGHT), GAME_CONSTS::NAME);
    window.setFramerateLimit(FPS_LIMIT);

    sf::Clock clock;
    RegistryApi api(pars.registry_ip);
    api.get_rooms();
    float load_delay = 5 * 1000;

    active([ ](sf::Event e) {}, [&clock, &load_delay, &api, &window, this]() {
        if (clock.getElapsedTime().asMilliseconds() >= load_delay) {
            clock.restart();
            api.get_rooms();
        }
        window.clear(sf::Color(255, 255, 255));
        draw_rooms(window, api.rooms);
        window.display();
    }, window);
}


