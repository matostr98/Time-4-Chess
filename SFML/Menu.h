#pragma once
#include <string>
#include <iostream>
#include "Icon.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Menu
{
private:
	
	void Create();
	void Destroy();
	void Textures();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;

	sf::Texture texture;
	sf::Sprite background;
	sf::Font font;

	Icon newGame;
	Icon online;
	Icon options;
	Icon guide;
	Icon about;
	Icon exit;

	bool cplay;
	bool conline;
	bool coptions;
	bool cguide;
	bool cabout;

public:
	Menu();
	Menu(const std::string& title, const sf::Vector2u& size);
	~Menu();

	void Setup(const std::string title, const sf::Vector2u& size);
	void Setup();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	//bool IsFullscreen();
	sf::Vector2u GetWindowSize();
	void Draw(sf::Drawable& l_drawable);
	void Close() { m_window.close(); }

	void Render();


	bool is_cplay() const {
		return cplay;
	}

	bool is_conline() const {
		return conline;
	}
};

