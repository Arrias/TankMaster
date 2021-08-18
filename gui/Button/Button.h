#pragma once

#include <SFML/Graphics.hpp>
#include "../../engine/entities/Block/Block.h"
#include "consts.h"

/*
 * the wrapper is above the timer,
 * it is necessary that when
 * the button is pressed for the first time,
 * it does not look at how much time has
 * passed since the last press
 */
class ActivateTimer {
    float delay;

public:
    ActivateTimer(float delay);

    sf::Clock clock;
    bool activated;

    bool isActive(); // return false if !activated || it's been less than delay milliseconds from last activate
};

class Button : public Block {
public:
    Button(Block base, sf::Texture *texture, sf::Texture *click_texture, sf::Text text);

    void draw(sf::RenderWindow &window);

    void click();

    void setCallback(const std::function<void()> &cf);

private:
    sf::Texture *texture, *click_texture;
    std::function<void()> callback = [ ]() {};
    sf::Text text;
    ActivateTimer timer = ActivateTimer(CLICK_DELAY);
};

