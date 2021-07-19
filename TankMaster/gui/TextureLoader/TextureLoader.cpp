#include "TextureLoader.h"

sf::Texture& TextureLoader::load_texture(std::string texture_path) {
	if (loaded_textures.find(texture_path) == loaded_textures.end()) {
		loaded_textures[texture_path].loadFromFile(texture_path);
	}
	return loaded_textures[texture_path];
}