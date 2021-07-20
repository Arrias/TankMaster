#include "GameView.h"
#include "../../gui/TextureLoader/TextureLoader.h"
#include "../../gui/constants.h"
#include <algorithm>

TextureLoader loader;

void draw_floor(int floor_type, sf::RenderWindow &window) {
    auto floor_texture = loader.load_texture(getPathToTexture(EntityType(ENTITY_NAME::FLOOR, floor_type)));

    int side_len = floor_texture->getSize().x; // == y because its square
    int grid_size = std::max((WINDOW::WIDTH + side_len - 1) / side_len, (WINDOW::HEIGHT + side_len - 1) / side_len);

    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            sf::Sprite square(*floor_texture);
            square.move(i * side_len, j * side_len);
            window.draw(square);
        }
    }
}

void draw_game(Game &game, sf::RenderWindow &window) {
    draw_floor(1, window);

    auto objs = game.get_objects();
    for (auto obj : objs) {
        auto texture = loader.load_texture(getPathToTexture(obj->get_type()));

        if (obj->get_type().name == ENTITY_NAME::TANK) {
            sf::Sprite sprite(*texture);
            sprite.setOrigin(TANK_CONSTS::WIDTH / 2, TANK_CONSTS::HEIGHT / 2);
            sprite.setPosition(obj->get_cords().x, obj->get_cords().y);
            sprite.setRotation(obj->get_angle());
            window.draw(sprite);
        }
    }
}