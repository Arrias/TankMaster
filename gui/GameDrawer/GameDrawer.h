#pragma once

#include <SFML/Graphics.hpp>
#include "../../engine/Game/Game.h"
#include "../../gui/TextureLoader/TextureLoader.h"

class GameDrawer {
    std::map<size_t, size_t> id_to_texture; // map id of block to num of texture
    Game *game;

    void draw_object(Block *obj, sf::RenderWindow &window, sf::Texture *texture);

    void draw_floor(sf::RenderWindow &window);

    TextureLoader loader;
public:
    void set_texture_num(size_t id, size_t texture_num);

    size_t floor_type;

    GameDrawer(Game *game, size_t floor_type);

    void draw_game(sf::RenderWindow &window);
};