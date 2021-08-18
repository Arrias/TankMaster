//
// Created by arrias on 31.07.2021.
//

#pragma once

#include "../Window/Window.h"
#include "../constants.h"

struct SingleGame : public Window {
    SingleGame(Window base);

    void show() override;
};


