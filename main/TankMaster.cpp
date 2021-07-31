#include "../gui/SingleGame/SingleGame.h"
#include "../engine/Game/Game.h"
#include <memory>

int main() {

    TextureLoader texture_loader;
    std::vector<shared_ptr<Window>> nav;

    nav.push_back(shared_ptr<Window>(new SingleGame(&nav, &texture_loader)));

    while (nav.size()) {
        nav.back()->active();
    }

    return 0;
}