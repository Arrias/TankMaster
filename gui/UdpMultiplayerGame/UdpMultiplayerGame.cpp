#include "UdpMultiplayerGame.h"
#include "../../gui/GameDrawer/GameDrawer.h"
#include <SFML/Network.hpp>
#include "consts.h"
#include <chrono>
#include <iostream>

const float wall_thick = 50;
const size_t floor_type = 3;

sf::IpAddress IP = sf::IpAddress::getLocalAddress();
int PORT = 2010;

struct TankController {
    sf::Keyboard::Key left, right, up, down, fire;

    TankController(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up,
                   sf::Keyboard::Key down, sf::Keyboard::Key fire) : left(left),
                                                                     right(right),
                                                                     up(up),
                                                                     down(down),
                                                                     fire(fire) {}

    bool shoot = false;
    bool moveUp = false;
    bool moveLeft = false;
    bool moveDown = false;
    bool moveRight = false;

    void update(sf::Event &e) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == fire) {
                shoot = true;
            }
            if (e.key.code == up) {
                moveUp = true;
            }
            if (e.key.code == down) {
                moveDown = true;
            }
            if (e.key.code == right) {
                moveRight = true;
            }
            if (e.key.code == left) {
                moveLeft = true;
            }
        } else if (e.type == sf::Event::KeyReleased) {
            if (e.key.code == up) {
                moveUp = false;
            }
            if (e.key.code == down) {
                moveDown = false;
            }
            if (e.key.code == right) {
                moveRight = false;
            }
            if (e.key.code == left) {
                moveLeft = false;
            }
        }
    }
};

void UdpMultiplayerGame::show() {
    sf::RenderWindow window(sf::VideoMode(MULTIPLAYER_GAME::WIDTH, MULTIPLAYER_GAME::HEIGHT), GAME_CONSTS::NAME);
    window.setFramerateLimit(FPS_LIMIT);
    window.setKeyRepeatEnabled(false);

    Game game;
    GameDrawer game_drawer(&game, floor_type, pars.texture_loader);

    TankController t(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::G);
    sf::Packet packet;
    packet << "registry!";
    socket.send(packet, IP, PORT);

    sf::Clock clock;
    active([&t, this](sf::Event event) {
        t.update(event);
        sf::Packet packet;
        packet << t.shoot << t.moveRight << t.moveLeft << t.moveDown << t.moveUp;
        socket.send(packet, IP, PORT);
        t.shoot = false;
    }, [&clock, &window, &game_drawer, &game, this]() {
        if (clock.getElapsedTime().asMilliseconds() < 1000 / FPS_LIMIT) return;

        sf::Packet packet;
        sf::IpAddress addr;
        unsigned short port;

        if (socket.receive(packet, addr, port) == sf::Socket::Status::Done)
            if (addr == IP && port == PORT)
                packet >> game;

        for (auto &i : game.get_blocks())
            game_drawer.set_texture_num(i->get_id(), 1);
        for (auto &i : game.get_tanks())
            game_drawer.set_texture_num(i->get_id(), 2);

        window.clear(sf::Color(0, 0, 0));
        game_drawer.draw_game(window);
        window.display();
        clock.restart();
    }, window);
}

UdpMultiplayerGame::UdpMultiplayerGame(Window base) : Window(base) {
    socket.setBlocking(false);
}