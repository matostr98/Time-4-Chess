#pragma once
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Icon.h"
#include <iostream>


class AfterMenu
{
private:

	void Create();
	void Destroy();
	void Textures();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool minimize;
	bool ngame;
	//bool m_isFullscreen;

	sf::Text text;

	sf::Texture texture;
	sf::Sprite background;
	sf::Font font;

	Icon newGame;
	Icon exit;
	Icon board;
public:
	AfterMenu();
	AfterMenu(const std::string& title, const sf::Vector2u& size);
	~AfterMenu();

	void Setup(const std::string title, const sf::Vector2u& size);
	void Setup();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	void Close() { m_window.close(); }
	//bool IsFullscreen();
	sf::Vector2u GetWindowSize();


	bool is_minimize() const {return minimize;}


	bool is_ngame() const {
		return ngame;
	}
	void ngameSetFalse() {
		ngame = false;
	}

	void Draw(sf::Drawable& l_drawable);
	void Render();
};

