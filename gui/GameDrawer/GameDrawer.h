#pragma once

#include <SFML/Graphics.hpp>
#include "../../engine/Game/Game.h"
#include "../../util/Loader/Loader.h"

class GameDrawer {
    std::map<size_t, size_t> id_to_texture; // map id of block to num of texture
    Loader<sf::Texture> *texture_loader;
    void draw_floor(sf::RenderWindow &window);

public:
    void set_texture_num(size_t id, size_t texture_num);

    size_t floor_type;

    GameDrawer(size_t floor_type, Loader<sf::Texture> *texture_loader);

    void draw_game(const Game &game, sf::RenderWindow &window);
};

void draw_object(Block *obj, sf::RenderWindow &window, sf::Texture *texture);