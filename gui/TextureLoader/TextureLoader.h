#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "../../engine/entities/MovableBlock/MovableBlock.h"

class TextureLoader {
private:
	std::map<std::string, sf::Texture*> loaded_textures;
public:
	sf::Texture* load_texture(std::string texture_path);

	sf::Texture* load_texture(EntityType entity_type);
};

std::string getPathToTexture(EntityType obj);