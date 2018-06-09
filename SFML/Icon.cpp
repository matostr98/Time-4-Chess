#include "Icon.h"



Icon::Icon()
{
}

Icon::Icon(sf::Vector2i pos, std::string src) {
	position = pos;
	source = src;
	texture.loadFromFile(src);
	sprite.setTexture(texture);
	sprite.setPosition(position.x, position.y);
	dimensions = { texture.getSize().x, texture.getSize().y };
}


Icon::~Icon()
{
}

void Icon::DrawButton(sf::RenderWindow& window) {
	window.draw(sprite);
}
