#include "MainMenu.h"
#include <string>
#include "../Button/Button.h"
#include "../SingleGame/SingleGame.h"
#include "../Registry/Registry.h"
#include "consts.h"
#include "../TcpMultiplayerGame/TcpMultiplayerGame.h"
#include "../../registry/API/RegistryApi.h"
#include "../../UdpGameHost/UdpGameHost.h"
#include "../UdpMultiplayerGame/UdpMultiplayerGame.h"

using std::pair;
using std::vector;
using std::string;
using sf::RenderWindow;
using sf::Sprite;
using sf::Text;
using sf::Color;
using sf::VideoMode;

vector<Button> buttons;

void MainMenu::make_menu(RenderWindow &window) {
    auto floor_texture = pars.texture_loader->load_item(Loader<sf::Texture>::get_path_to_texture("floors", menu_floor_type));
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

    auto &single_game_button = buttons[0];
    auto &add_room_button = buttons[1];
    auto &join_room_button = buttons[2];
    auto &exit_button = buttons[3];

    single_game_button.setCallback([&window, this]() {
        window.close();
        pars.nav->push_back(shared_ptr<Window>(new SingleGame(Window(pars))));
    });

    add_room_button.setCallback([&window, this]() {
        unsigned short port = 2009;
        Room room;
        Room::Identifier id;
        room.creator_name = "Player";
        room.address = {"127.0.0.1", std::to_string(port)};
        room.places_cnt = 2;
        room.free_places = 2;

        RegistryApi api(pars.registry_ip);
        if(api.create_room(room, id)) {
            window.close();
            pars.games->push_back(std::make_shared<UdpGameHost>(room, id, pars.registry_ip));
            pars.games->back()->launch();
            pars.nav->push_back(shared_ptr<Window>(new UdpMultiplayerGame(room, Window(pars))));
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
    auto button_texture = pars.texture_loader->load_item(Loader<sf::Texture>::get_path_to_texture("buttons", 1));
    auto active_button_texture = pars.texture_loader->load_item(Loader<sf::Texture>::get_path_to_texture("buttons", 2));

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

