#pragma once
#include <map>
#include <string>

enum class ENTITY_NAME {
	TANK,
	WALL,
};

struct EntityType {
	ENTITY_NAME name;
	size_t num;

	EntityType(ENTITY_NAME name, size_t num); 

	static std::string entity_name_to_string(ENTITY_NAME name);
};
