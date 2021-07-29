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

void draw(Block *obj, sf::RenderWindow &window, sf::Texture *texture) {
    sf::Sprite sprite(*texture, sf::IntRect(0, 0, obj->get_size().x, obj->get_size().y));
    texture->setRepeated(true);
    texture->setSmooth(true);
    sprite.setOrigin(obj->get_size().x / 2, obj->get_size().y / 2);
    sprite.setPosition(obj->get_cords().x, obj->get_cords().y);
    sprite.setRotation(obj->get_angle());
    window.draw(sprite);
}

void draw_game(Game &game, sf::RenderWindow &window) {
    //draw_floor(2, window);

    auto objs = game.get_objects();
    for (auto obj : objs) {
        auto texture = loader.load_texture(obj->get_type());
        draw(obj, window, texture);
    }
}