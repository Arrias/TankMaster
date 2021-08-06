#pragma once

#include "../Window/Window.h"
#include "../constants.h"

struct MultiplayerGame : public Window {
    MultiplayerGame(vector<shared_ptr<Window>> *nav, TextureLoader *texture_loader);

    void active() override;
};


