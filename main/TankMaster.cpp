#include "../gui/SingleGame/SingleGame.h"
#include "../gui/MainMenu/MainMenu.h"

int main(int argc, char *argv[]) {
    TextureLoader texture_loader;
    std::vector<shared_ptr<Window>> nav;
    nav.push_back(shared_ptr<Window>(new MainMenu(&nav, &texture_loader)));
    // nav.push_back(shared_ptr<Window>(new SingleGame(&nav, &texture_loader)));
    while (nav.size()) {
        nav.back()->active();
    }
    return 0;
}