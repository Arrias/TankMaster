//
// Created by arrias on 31.07.2021.
//

#include "MainMenu.h"
#include "../constants.h"
#include <string>
#include "../Button/Button.h"
#include "../SingleGame/SingleGame.h"
#include "../Registry/Registry.h"
#include "consts.h"
#include "../TcpMultiplayerGame/TcpMultiplayerGame.h"
#include "../../registry/API/RegistryApi.h"

using std::vector;
using std::string;
using sf::RenderWindow;
using sf::Sprite;
using sf::Text;
using sf::Color;
using sf::VideoMode;

vector<Button> buttons;

void MainMenu::make_menu(RenderWindow &window) {
    auto floor_texture = pars.texture_loader->load_item("floors", menu_floor_type);
    Sprite floor(*floor_texture);
    window.draw(floor);

    Text title;
    title.setString(GAME_CONSTS::NAME);
    title.setFont(*pars.font_loader->load_item(path_to_font));
    title.setFillColor(Color(0, 0, 0));
    title.setCharacterSize(title_letter_size);
    auto textSizes = title.getGlobalBounds();
    title.setOrigin(textSizes.width / 2, textSizes.height / 2);
    title.setPosition(title_pos.to_sfml_vector());

    window.draw(title);
    for (auto &button : buttons) {
        button.draw(window);
    }
}

void MainMenu::show() {
    RenderWindow window(VideoMode(MAIN_MENU::WIDTH, MAIN_MENU::HEIGHT), GAME_CONSTS::NAME, sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(FPS_LIMIT);

    // buttons = {single game, multiplayer game, add room, all rooms, exit}

    auto &single_game_button = buttons[0];
    auto &add_room_button = buttons[1];
    auto &join_room_button = buttons[2];
    auto &exit_button = buttons[3];

    single_game_button.setCallback([&window, this]() {
        window.close();
        pars.nav->push_back(shared_ptr<Window>(new SingleGame(Window(pars))));
    });

    add_room_button.setCallback([&window, this] {
        RegistryApi api(pars.registry_ip);
        Room room;
        room.creator_name = "Player";
        room.address = {"http://localhost", "2010"};
        room.free_places = 1;
        room.places_cnt = 1;

        if(api.create_room(room)) {
            window.close();
            pars.nav->push_back(shared_ptr<Window>(new TcpMultiplayerGame(room, Window(pars))));
        }
    });

    join_room_button.setCallback([&window, this]() {
        window.close();
        pars.nav->push_back(shared_ptr<Window>(new Registry(Window(pars))));
    });

    exit_button.setCallback([&window, this]() {
        window.close();
        pars.nav->clear();
    });

    active([ ](sf::Event e) {}, [&window, this]() {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto mouseX = sf::Mouse::getPosition(window).x;
            auto mouseY = sf::Mouse::getPosition(window).y;
            for (auto &button : buttons) {
                if (point_in_block(Vector(mouseX, mouseY), &button)) {
                    button.click();
                }
            }
        }
        window.clear(Color(0, 0, 0));
        make_menu(window);
        window.display();
    }, window);
}

MainMenu::MainMenu(Window base) : Window(base) {
    auto button_texture = pars.texture_loader->load_item("buttons", 1);
    auto active_button_texture = pars.texture_loader->load_item("buttons", 2);

    auto get_button_with_text = [this](string title) {
        Text text;
        text.setString(title);
        text.setFillColor(Color(0, 0, 0));
        text.setFont(*pars.font_loader->load_item(path_to_font));
        text.setCharacterSize(buttons_letter_size);
        return text;
    };

    buttons = {
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 3),
                         button_size, 0, 0),
                   button_texture, active_button_texture, get_button_with_text("Single Game")),
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 4),
                         button_size, 0, 0),
                   button_texture, active_button_texture, get_button_with_text("Add Room")),
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 5),
                         button_size, 0, 0),
                   button_texture, active_button_texture, get_button_with_text("Join room")),
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 6),
                         button_size, 0, 0),
                   button_texture, active_button_texture, get_button_with_text("Exit")),
    };
}

