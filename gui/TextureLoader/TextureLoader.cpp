#include "TextureLoader.h"
#include <sstream>

sf::Texture* TextureLoader::load_texture(std::string texture_path) {
	if (loaded_textures.find(texture_path) == loaded_textures.end()) {
		loaded_textures[texture_path] = new sf::Texture();
		loaded_textures[texture_path]->loadFromFile(texture_path);
	}
	return loaded_textures[texture_path];
}

std::string getPathToTexture(MovableObject& obj) {
	auto type = obj.get_type();
	std::stringstream ret;
	ret << "../";
	ret << "textures/";
	ret << EntityType::entity_name_to_string(type.name);
	ret << "/";
	ret << std::to_string(type.num);
	ret << ".png";
	return ret.str();
}
