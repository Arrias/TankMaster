#include "Registry.h"
#include "../../registry/API/RegistryApi.h"
#include "consts.h"
#include "../TcpMultiplayerGame/TcpMultiplayerGame.h"
#include "../UdpMultiplayerGame/UdpMultiplayerGame.h"
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

    buttons.clear();
    Vector but_size = Vector(700, 100);
    Vector cords = Vector(360, 60 );

    auto button_texture = pars.texture_loader->load_item(Loader<sf::Texture>::get_path_to_texture("buttons", 1));
    auto active_button_texture = pars.texture_loader->load_item(Loader<sf::Texture>::get_path_to_texture("buttons", 2));

    for (auto &room : rooms) {
        buttons.emplace_back(Block(cords, but_size, 0, 0),
                                 button_texture, active_button_texture,
                                 get_button_with_text(room.creator_name.value + " " +
                                 room.address.value.getAddress() + " " +
                                 std::to_string(room.free_places.value) + "/" +
                                 std::to_string(room.places_cnt.value) +
                                 " free places"));

        buttons.back().setCallback([&room, &window, this]() {
            window.close();
            pars.nav->push_back(shared_ptr<Window>(new UdpMultiplayerGame(room, Window(pars))));
        });
        cords.y += but_size.y + 10;
    }

    for (auto &but : buttons) {
        but.draw(window);
    }
}

void Registry::show() {
    sf::RenderWindow window(sf::VideoMode(REGISTRY::WIDTH, REGISTRY::HEIGHT), GAME_CONSTS::NAME);
    window.setFramerateLimit(FPS_LIMIT);

    RegistryApi api(pars.registry_ip);
    api.get_rooms();
    window.clear(sf::Color(255, 255, 255));
    draw_rooms(window, api.rooms);
    window.display();

    sf::Clock clock;
    float load_delay = 5 * 1000;

    active([ ](sf::Event e) {}, [&clock, &load_delay, &api, &window, this]() {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto mouseX = sf::Mouse::getPosition(window).x;
            auto mouseY = sf::Mouse::getPosition(window).y;
            for (auto &button : buttons) {
                if (point_in_block(Vector(mouseX, mouseY), &button)) {
                    button.click();
                }
            }
        }
        if (clock.getElapsedTime().asMilliseconds() >= load_delay) {
            clock.restart();
            api.get_rooms();
        }
        window.clear(sf::Color(255, 255, 255));
        draw_rooms(window, api.rooms);
        window.display();
    }, window);
}


