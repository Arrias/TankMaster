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

const float CLICK_DELAY = 4998;

void Button::draw(sf::RenderWindow &window) {
    auto delta = (clock() - last_clicked);
    bool clicked = delta < CLICK_DELAY;
    draw_object(this, window, (clicked ? click_texture : texture));
    window.draw(text);
}

void Button::click() {
    auto delta = (clock() - last_clicked);
    if (delta < CLICK_DELAY) return;
    last_clicked = clock();
    callback();
}

void Button::setCallback(const std::function<void()> &cf) {
    callback = cf;
}
