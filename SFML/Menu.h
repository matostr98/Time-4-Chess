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

	std::map<std::string, sf::Texture> TextureMap;
	//sf::Texture texture;
	sf::Sprite background;
	sf::Sprite m_credits;
	sf::Sprite m_guide;
	sf::Sprite m_options;
	sf::Font font;

	Icon newGame;
	Icon online;
	Icon options;
	Icon guide;
	Icon about;
	Icon exit;
	Icon back;

	//options buttons
	Icon t3;
	Icon t5;
	Icon t10;
	Icon t15;
	Icon t20;
	Icon t30;
	Icon t45;
	Icon t60;
	Icon t90;

	bool main;
	bool cplay;
	bool conline;
	bool coptions;
	bool cguide;
	bool cabout;

	float timer;

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


	float get_timer() const {
		return timer;
	}
};

