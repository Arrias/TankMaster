#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <sstream>

template<class T>
class Loader {
    std::map<std::string, T *> loaded_items;

public:

    static std::string get_path_to_texture(std::string entity_type, size_t texture_num) {
        std::stringstream ret;
        ret << "../textures/";
        ret << entity_type;
        ret << "/";
        ret << std::to_string(texture_num);
        ret << ".png";
        return ret.str();
    }

    T *load_item(std::string item_path) {
        if (loaded_items.find(item_path) == loaded_items.end()) {
            loaded_items[item_path] = new T();
            loaded_items[item_path]->loadFromFile(item_path);
        }
        return loaded_items[item_path];
    }

    ~Loader() {
        for (auto &i : loaded_items) {
            delete i.second;
        }
    }
};
