#pragma once
#include <string>
#include <sstream>
#include "../gui/constants.h"

namespace WINDOW {
	const size_t HEIGHT = 900;
	const size_t WIDTH = 1500;
}

namespace TANK_CONSTS {
	namespace BASE {
		const float SPEED = 0.4;
		const float ROTATION = 0.2;
		const float SCALE = 0.5;
	}

	const float PIC_HEIGHT = 202;
	const float PIC_WIDTH = 148;

	const float HEIGHT = PIC_HEIGHT * BASE::SCALE;
	const float WIDTH = PIC_WIDTH * BASE::SCALE;
}
