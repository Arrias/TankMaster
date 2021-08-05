#pragma once

#include <string>
#include <sstream>
#include "../gui/constants.h"

const int FPS_LIMIT = 50;

namespace GAME_CONSTS {
    const std::string NAME = "TankMaster";
    const std::string version = "0.0.1";
}

namespace WINDOWS_CONSTS {
    namespace SINGLE_GAME {
        const size_t HEIGHT = 900;
        const size_t WIDTH = 1600;
    }
    namespace MAIN_MENU {
        const size_t HEIGHT = 600;
        const size_t WIDTH = 800;
    }
}

namespace TANK_CONSTS {
    namespace BASE {
        const float SPEED = 0.4;
        const float ROTATION = 0.4;
    }

    const float HEIGHT = 82;
    const float WIDTH = 60;
}

namespace BULLET_CONSTS {
    namespace BASE {
        const float SPEED = 0.5;
    }

    const float HEIGHT = 14;
    const float WIDTH = 14;
}