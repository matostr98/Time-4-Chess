#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Icon
{
private:
	sf::Vector2i position;
	sf::Texture texture;
	sf::Sprite sprite;
	std::string source;
	sf::Vector2i dimensions;
public:
	Icon();
	Icon(sf::Vector2i pos, std::string src);
	~Icon();

	void DrawButton(sf::RenderWindow& window);


	sf::Vector2i get_position() const {return position;}
	void set_position(const sf::Vector2i& position) {this->position = position;}

	std::string get_source() const {return source;}
	void set_source(const std::string& source) {this->source = source;}

	sf::Vector2i get_dimensions() const {return dimensions;}
	void set_dimensions(const sf::Vector2i& dimensions) {this->dimensions = dimensions;}
};

