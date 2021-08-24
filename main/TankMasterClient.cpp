#include "../gui/SingleGame/SingleGame.h"
#include "../gui/MainMenu/MainMenu.h"
#include "../UdpGameHost/UdpGameHost.h"

int main(int argc, char *argv[]) {
    // Initialize parameters
    std::vector<shared_ptr<UdpGameHost>> my_games;
    Loader<sf::Texture> texture_loader;
    Loader<sf::Font> font_loader;
    std::vector<shared_ptr<Window>> nav;
    std::string registry_address = (argc > 1) ? argv[1] : "";
    std::string registry_port = (argc > 2) ? argv[2] : "";

    nav.push_back(shared_ptr<Window>(new MainMenu(Window({&my_games, &nav, &texture_loader, &font_loader, {registry_address, registry_port}}))));
    while (nav.size()) {
        nav.back()->show();
    }
    return 0;
}