#include "EnityType.h"
#include <cassert>

EntityType::EntityType(ENTITY_NAME name, size_t num) : name(name), num(num) {}

std::string EntityType::entity_name_to_string(ENTITY_NAME name) {
	if (name == ENTITY_NAME::TANK) return "tanks";
	if (name == ENTITY_NAME::WALL) return "wall";
	// TODO 
	assert(false);
}
