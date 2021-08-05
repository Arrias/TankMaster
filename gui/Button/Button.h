#pragma once

#include <SFML/Graphics.hpp>
#include "../../engine/entities/Block/Block.h"
#include <chrono>

class Button : public Block {
public:
    sf::Texture *texture, *click_texture;
    std::function<void()> callback = [ ]() {};
    sf::Text text;

    Button(Block base, sf::Texture *texture, sf::Texture *click_texture, sf::Text text);

    void draw(sf::RenderWindow &window);

    void click();

    void setCallback(const std::function<void()> &cf);

private:
    float last_clicked = clock();
};

