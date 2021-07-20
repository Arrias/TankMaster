#include "TextureLoader.h"
#include <sstream>

sf::Texture* TextureLoader::load_texture(std::string texture_path) {
	if (loaded_textures.find(texture_path) == loaded_textures.end()) {
		loaded_textures[texture_path] = new sf::Texture();
		loaded_textures[texture_path]->loadFromFile(texture_path);
	}
	return loaded_textures[texture_path];
}

sf::Texture *TextureLoader::load_texture(EntityType entity_type) {
    auto path = getPathToTexture(entity_type);
    return load_texture(path);
}

std::string getPathToTexture(EntityType type) {
	std::stringstream ret;
	ret << "../";
	ret << "textures/";
	ret << EntityType::entity_name_to_string(type.name);
	ret << "/";
	ret << std::to_string(type.num);
	ret << ".png";
	return ret.str();
}
