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
	dimensions = texture.getSize();
}


Icon::~Icon()
{
}

void Icon::DrawButton(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Icon::Setup(sf::Vector2i position, std::string source) {
	this->position = position;
	this->source = source;

	texture.loadFromFile(source);
	sprite.setTexture(texture);
	sprite.setPosition({(float)position.x, (float)position.y});
}
