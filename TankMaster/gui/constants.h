#pragma once
#include <string>
#include <sstream>

namespace WINDOW {
	const double HEIGHT = 900;
	const double WIDTH = 1500;
}

namespace TANK_CONSTS {
	const double HEIGHT = 202;
	const double WIDTH = 148;

	namespace BASE {
		const double SPEED = 0.5;
		const double ROTATION = 0.1;
		const double ORIGIN = 50.0;
		const double SCALE = 0.6;
	}
}

std::string getPathToTexture(std::string entity_type, int entity_num) {
	std::stringstream ret;
	ret << "textures\\";
	ret << entity_type + "s\\";
	ret << std::to_string(entity_num);
	ret << ".png";
	return ret.str();
}