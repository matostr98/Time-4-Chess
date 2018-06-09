#include "Menu.h"



Menu::Menu() { Setup("Window", sf::Vector2u(700, 400)); }
Menu::Menu(const std::string& title, const sf::Vector2u& size) { Setup(title, size); }
Menu::~Menu() { Destroy(); }

void Menu::Setup(const std::string title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	m_window.setFramerateLimit(60);
	Create();
}

void Menu::Create() {
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, sf::Style::Titlebar);
}

void Menu::Destroy() {
	m_window.close();
}


void Menu::BeginDraw() { m_window.clear(sf::Color::Black); }
void Menu::EndDraw() { m_window.display(); }

bool Menu::IsDone() { return m_isDone; }

void Menu::Draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}

sf::Vector2u Menu::GetWindowSize() { return m_windowSize; }



void Menu::Update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { m_isDone = true; }
		//else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) { ToggleFullscreen(); }
	}
}