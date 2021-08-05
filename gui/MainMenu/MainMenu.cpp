//
// Created by arrias on 31.07.2021.
//

#include "MainMenu.h"
#include "../constants.h"
#include <string>
#include "../Button/Button.h"
#include "../SingleGame/SingleGame.h"
#include <iostream>

using namespace sf;
using namespace std;

const string path_to_font = "../fonts/ALoveOfThunder/A Love of Thunder.ttf";
const size_t menu_floor_type = 5;
const size_t title_letter_size = 100;
const size_t buttons_letter_size = 24;
const size_t button_margin = 50;
Vector title_pos = Vector(WINDOWS_CONSTS::MAIN_MENU::WIDTH / 2., WINDOWS_CONSTS::MAIN_MENU::HEIGHT / 8.);
Vector button_size = {250, 35};

Font font;
vector<Button> buttons;

void MainMenu::make_menu(RenderWindow &window) {
    auto floor_texture = texture_loader->load_texture("floors", menu_floor_type);
    Sprite floor(*floor_texture);
    window.draw(floor);

    Text title;
    title.setString(GAME_CONSTS::NAME);
    title.setFont(font);
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

void MainMenu::active() {
    RenderWindow window(VideoMode(WINDOWS_CONSTS::MAIN_MENU::WIDTH, WINDOWS_CONSTS::MAIN_MENU::HEIGHT), GAME_CONSTS::NAME);
    window.setFramerateLimit(FPS_LIMIT);

    auto &nav_ref = nav;
    auto txt_loader = texture_loader;

    buttons[0].setCallback([&window, &nav_ref, &txt_loader]() {
        window.close();
        nav_ref->push_back(shared_ptr<Window>(new SingleGame(nav_ref, txt_loader)));
    });

    buttons.back().setCallback([&window, &nav_ref]() { // Exit button
        window.close();
        nav_ref->clear();
    });

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                nav->clear();
                break;
            }
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            auto mouseX = Mouse::getPosition(window).x;
            auto mouseY = Mouse::getPosition(window).y;
            for (auto &button : buttons) {
                if (point_in_block(Vector(mouseX, mouseY), &button)) {
                    button.click();
                }
            }
        }
        window.clear(Color(0, 0, 0));
        make_menu(window);
        window.display();
    }
}

MainMenu::MainMenu(vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader) : Window(nav, texture_loader) {
    font.loadFromFile(path_to_font);

    auto button_texture = texture_loader->load_texture("buttons", 1);
    auto active_button_texture = texture_loader->load_texture("buttons", 2);

    auto getButtonText = [ ](string title) {
        Text text;
        text.setString(title);
        text.setFillColor(Color(0, 0, 0));
        text.setFont(font);
        text.setCharacterSize(buttons_letter_size);
        return text;
    };

    buttons = {
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 3),
                         button_size, 0, 0),
                   button_texture, active_button_texture, getButtonText("Single Game")),
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 4),
                         button_size, 0, 0),
                   button_texture, active_button_texture, getButtonText("Add Room")),
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 5),
                         button_size, 0, 0),
                   button_texture, active_button_texture, getButtonText("Join room")),
            Button(Block(Vector(title_pos.x, title_pos.y + button_margin * 6),
                         button_size, 0, 0),
                   button_texture, active_button_texture, getButtonText("Exit")),
    };
}
