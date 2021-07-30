#pragma once
#include <string>
#include <sstream>
#include "../gui/constants.h"

namespace WINDOW {
	const size_t HEIGHT = 900;
	const size_t WIDTH = 1600;
}

namespace TANK_CONSTS {
	namespace BASE {
		const float SPEED = 0.3;
		const float ROTATION = 0.3;
	}

	const float HEIGHT = 82;
	const float WIDTH = 60;
}

namespace BULLET_CONSTS {
    namespace BASE {
        const float SPEED = 0.3;
    }

    const float HEIGHT = 14;
    const float WIDTH = 14;
}