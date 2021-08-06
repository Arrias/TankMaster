#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../engine/Game/Game.h"
#include "../gui/constants.h"
#include "../gui/MultiplayerGame/MultiplayerGame.h"
#include <memory>
#include <iostream>

using namespace std; // WTF DUDE?

int main() {

    TextureLoader texture_loader;
    std::vector<shared_ptr<Window>> nav;
    nav.push_back(shared_ptr<Window>(new MultiplayerGame(&nav, &texture_loader)));

    while (!nav.empty()) {
        nav.back()->active();
    }
	return 0;
}