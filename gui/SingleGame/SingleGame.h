#pragma once

#include "../Window/Window.h"
#include "../constants.h"

struct SingleGame : public Window {
    SingleGame(vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader);

    void active() override;
};


