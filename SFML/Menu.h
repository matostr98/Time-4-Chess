#pragma once
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Menu
{
private:
	
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	//bool m_isFullscreen;
public:
	Menu();
	Menu(const std::string& title, const sf::Vector2u& size);
	~Menu();

	void Setup(const std::string title, const sf::Vector2u& size);

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	//bool IsFullscreen();
	sf::Vector2u GetWindowSize();


	void Draw(sf::Drawable& l_drawable);
};

