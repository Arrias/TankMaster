#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>

class TextureLoader {
private:
	std::map<std::string, sf::Texture*> loaded_textures;

	static std::string get_path_to_texture(std::string entity_type, size_t texture_num);

public:
	sf::Texture* load_texture(std::string texture_path);

	sf::Texture* load_texture(std::string entity_type, size_t texture_num);

	~TextureLoader();
};