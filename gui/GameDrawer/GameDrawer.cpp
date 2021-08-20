#include "GameDrawer.h"
#include <algorithm>

const std::string FLOOR = "floors";
const std::string TANK = "tanks";
const std::string WALL = "walls";
const std::string BULLET = "bullets";
const std::string BOOSTER = "boosters";

void draw_object(Block *obj, sf::RenderWindow &window, sf::Texture *texture) {
    sf::Sprite sprite(*texture, sf::IntRect(0, 0, obj->get_size().x, obj->get_size().y));
    texture->setRepeated(true);
    texture->setSmooth(true);
    sprite.setOrigin(obj->get_size().x / 2, obj->get_size().y / 2);
    sprite.setPosition(obj->get_cords().x, obj->get_cords().y);
    sprite.setRotation(obj->get_angle());
    window.draw(sprite);
}

void GameDrawer::draw_game(sf::RenderWindow &window) {
    draw_floor(window);

    for (auto block : game->get_blocks()) {
        auto texture = texture_loader->load_texture(WALL, id_to_texture[block->get_id()]);
        draw_object(block.get(), window, texture);
    }
    for (auto booster : game->get_boosters()) {
        auto texture = texture_loader->load_texture(BOOSTER, id_to_texture[booster->get_id()]);
        draw_object(booster.get(), window, texture);
    }

    for (auto tank : game->get_tanks()) {
        auto texture = texture_loader->load_texture(TANK, id_to_texture[tank->get_id()]);
        draw_object(tank.get(), window, texture);
    }

    for (auto bullet : game->get_bullets()) {
        //auto texture = texture_loader->load_texture(BULLET, id_to_texture[bullet->get_id()]);
        auto texture = texture_loader->load_texture(BULLET, 1);
        draw_object(bullet.get(), window, texture);
    }
}

void GameDrawer::draw_floor(sf::RenderWindow &window) {
    auto floor_texture = texture_loader->load_texture(FLOOR, floor_type);
    sf::Sprite square(*floor_texture);
    window.draw(square);
}

void GameDrawer::set_texture_num(size_t id, size_t texture_num) {
    id_to_texture[id] = texture_num;
}

GameDrawer::GameDrawer(Game *game, size_t floor_type, TextureLoader *texture_loader) : game(game), floor_type(floor_type),
                                                                                       texture_loader(texture_loader) {}
