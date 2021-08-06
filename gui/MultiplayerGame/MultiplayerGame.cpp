#include "MultiplayerGame.h"
#include "../../gui/GameDrawer/GameDrawer.h"
#include <SFML/Network.hpp>
#include <chrono>

using namespace sf;

const float wall_thick = 50;
const size_t floor_type = 3;
const int FPS = 40;
IpAddress IP = IpAddress::getLocalAddress();
int PORT = 2000;

void MultiplayerGame::active() {
    Game game;
    GameDrawer game_drawer(&game, floor_type, texture_loader);
    RenderWindow window(VideoMode(WINDOWS_CONSTS::SINGLE_GAME::WIDTH, WINDOWS_CONSTS::SINGLE_GAME::HEIGHT), GAME_CONSTS::NAME);

    sf::TcpSocket socket;

    if (socket.connect(IP, PORT) == sf::Socket::Status::Done) {
        sf::Clock fps_clock;
        bool moveForward = false, moveRight = false, moveLeft = false, moveBack = false;

        while (window.isOpen()) {
            Event event;
            if (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { // LEAVE TANKS
                    window.close();
                    nav->clear();
                    break;
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Right)
                        moveRight = true;
                    else if (event.key.code == sf::Keyboard::Left)
                        moveLeft = true;
                    else if (event.key.code == sf::Keyboard::Up)
                        moveForward = true;
                    else if (event.key.code == sf::Keyboard::Down)
                        moveBack = true;
                } else if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Right)
                        moveRight = false;
                    else if (event.key.code == sf::Keyboard::Left)
                        moveLeft = false;
                    else if (event.key.code == sf::Keyboard::Up)
                        moveForward = false;
                    else if (event.key.code == sf::Keyboard::Down)
                        moveBack = false;
                }
            }

            if (fps_clock.getElapsedTime().asMilliseconds() >= 1000 / FPS) {
                fps_clock.restart();

                if(moveRight || moveLeft || moveBack || moveForward) {
                    sf::Packet packet; //SEND USER INPUT
                    packet << moveRight << moveLeft << moveBack << moveForward;
                    socket.send(packet);
                }

                sf::Packet packet; //RECEIVE GAME AND REDRAW
                if (socket.receive(packet) == sf::Socket::Status::Done)
                    packet >> game;

                for(auto &i : game.get_blocks())
                    game_drawer.set_texture_num(i->get_id(), 1);
                for(auto &i : game.get_tanks())
                    game_drawer.set_texture_num(i->get_id(), 2);

                window.clear(Color(0, 0, 0));
                game_drawer.draw_game(window);
                window.display();
            }
        }
    }
}

MultiplayerGame::MultiplayerGame(std::vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader) : Window(nav,
                                                                                                               texture_loader) {}















