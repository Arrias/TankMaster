#pragma once

#include <string>
#include "../../util/geometry/Vector/Vector.h"

namespace MAIN_MENU {
    const size_t HEIGHT = 600;
    const size_t WIDTH = 800;
}

const std::string path_to_font = "../fonts/ALoveOfThunder/A Love of Thunder.ttf";
const size_t menu_floor_type = 5;
const size_t title_letter_size = 100;
const size_t buttons_letter_size = 24;
const size_t button_margin = 50;
const Vector title_pos = Vector(MAIN_MENU::WIDTH / 2., MAIN_MENU::HEIGHT / 8.);
const Vector button_size = {250, 35};

