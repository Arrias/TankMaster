#include "Button.h"
#include "../GameDrawer/GameDrawer.h"

Button::Button(Block base, sf::Texture *texture, sf::Texture *click_texture, sf::Text text) : Block(base),
                                                                                              texture(texture),
                                                                                              click_texture(click_texture),
                                                                                              text(text) {
    auto text_size = text.getGlobalBounds();
    this->text.setOrigin(text_size.width / 2, text_size.height / 2 + 5);
    this->text.setPosition(base.get_cords().x, base.get_cords().y);
}

void Button::draw(sf::RenderWindow &window) {
    draw_object(this, window, (timer.isActive() ? click_texture : texture));
    window.draw(text);
}

void Button::click() {
    if (timer.isActive()) return;
    timer.activated = true;
    timer.clock.restart();
    callback();
}

void Button::setCallback(const std::function<void()> &cf) {
    callback = cf;
}

ActivateTimer::ActivateTimer(float delay) : delay(delay) {}

bool ActivateTimer::isActive() {
    if (!activated) return false;
    if (clock.getElapsedTime().asMilliseconds() > delay) return false;
    return true;
}
