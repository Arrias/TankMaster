#include "TextureLoader.h"
#include <sstream>

sf::Texture *TextureLoader::load_texture(std::string texture_path) {
    if (loaded_textures.find(texture_path) == loaded_textures.end()) {
        loaded_textures[texture_path] = new sf::Texture();
        loaded_textures[texture_path]->loadFromFile(texture_path);
    }
    return loaded_textures[texture_path];
}

std::string TextureLoader::get_path_to_texture(std::string entity_type, size_t texture_num) {
    std::stringstream ret;
    ret << "../textures/";
    ret << entity_type;
    ret << "/";
    ret << std::to_string(texture_num);
    ret << ".png";
    return ret.str();
}

sf::Texture *TextureLoader::load_texture(std::string entity_type, size_t texture_num) {
    auto path = get_path_to_texture(entity_type, texture_num);
    return load_texture(path);
}

TextureLoader::~TextureLoader() {
    for (auto &i : loaded_textures) {
        delete i.second;
    }
}

