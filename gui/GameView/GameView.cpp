#include "GameView.h"
#include "../../gui/TextureLoader/TextureLoader.h"
#include "../../gui/constants.h"

TextureLoader loader;

void draw_game(Game& game, sf::RenderWindow& window) {
	auto objs = game.get_objects();
	
	for (auto obj : objs) {
		auto texture = loader.load_texture(getPathToTexture(*obj));

		if (obj->get_type().name == ENTITY_NAME::TANK) {
			sf::Sprite sprite(*texture);
			sprite.setOrigin(TANK_CONSTS::PIC_WIDTH / 2, TANK_CONSTS::PIC_HEIGHT / 2);
			sprite.setPosition(obj->get_cords().x, obj->get_cords().y);
			sprite.setRotation(obj->get_angl());
			sprite.setScale(TANK_CONSTS::BASE::SCALE, TANK_CONSTS::BASE::SCALE);
			window.draw(sprite);
		}
	}
}