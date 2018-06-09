#include "Menu.h"



Menu::Menu() { Setup("Time-4-Chess", sf::Vector2u(1280, 720)); }
Menu::Menu(const std::string& title, const sf::Vector2u& size) { Setup(title, size); }
Menu::~Menu() { Destroy(); }

void Menu::Setup(const std::string title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	m_window.setFramerateLimit(60);
	Create();
	Textures();
}

void Menu::Create() {
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, sf::Style::Titlebar);
}

void Menu::Destroy() {
	m_window.close();
}

void Menu::Textures() {
	texture.loadFromFile("Assets/Textures/Menus/m_main.png");
	background.setTexture(texture);

	newGame.Setup({ 220, 270 }, "Assets/Textures/Buttons/bb_play.png");
	online.Setup({ 670, 270 }, "Assets/Textures/Buttons/bb_online.png");
	options.Setup({ 220, 410 }, "Assets/Textures/Buttons/bb_options.png");
	guide.Setup({ 670, 410 }, "Assets/Textures/Buttons/bb_guide.png");
	about.Setup({ 220, 550 }, "Assets/Textures/Buttons/bb_credits.png");
	exit.Setup({ 670, 550 }, "Assets/Textures/Buttons/bb_exit.png");
}


void Menu::BeginDraw() { m_window.clear(sf::Color::Black); }
void Menu::EndDraw() { m_window.display(); }

bool Menu::IsDone() { return m_isDone; }

void Menu::Draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}

void Menu::Render() {
	BeginDraw();

	m_window.draw(background);
	online.DrawButton(m_window);
	options.DrawButton(m_window);
	guide.DrawButton(m_window);
	about.DrawButton(m_window);
	exit.DrawButton(m_window);
	newGame.DrawButton(m_window);

	EndDraw();
}

sf::Vector2u Menu::GetWindowSize() { return m_windowSize; }



void Menu::Update() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (m_isDone == true) {m_window.close();}

		switch (event.type) {
		case sf::Event::Closed: { m_isDone = true; break; }
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Escape: {m_isDone = true; m_window.close(); break; }
									   //case sf::Keyboard::Right: {music.nextSong(); music.next(); break; }
			}
		case sf::Event::MouseButtonPressed:
			switch (event.key.code) {

			case sf::Mouse::Left: {
				//if left button is clicked
				sf::Vector2i MouseCoordinates = sf::Mouse::getPosition(m_window);

				if (MouseCoordinates.x >= newGame.get_position().x &&
					MouseCoordinates.x < 610 &&
					MouseCoordinates.y >= newGame.get_position().y &&
					MouseCoordinates.y < 380) {
					//std::cout << "Exit\n";
					cplay = true;
				}

				if (MouseCoordinates.x >= online.get_position().x &&
					MouseCoordinates.x < 1060 &&
					MouseCoordinates.y >= online.get_position().y &&
					MouseCoordinates.y < 380) {
					std::cout << "Chyba kogos pojebalo z zgloszeniem tej funkcjonalnosci\n";
					std::cout << "Zaraz, to ja sam sie tak udupilem\n";
					//m_isDone = true;
				}

				if (MouseCoordinates.x >= options.get_position().x &&
					MouseCoordinates.x < 610 &&
					MouseCoordinates.y >= options.get_position().y &&
					MouseCoordinates.y < 520) {
					//std::cout << "Exit\n";
					//m_isDone = true;
				}

				if (MouseCoordinates.x >= guide.get_position().x &&
					MouseCoordinates.x < 1060 &&
					MouseCoordinates.y >= guide.get_position().y &&
					MouseCoordinates.y < 520) {
					//std::cout << "Exit\n";
					//m_isDone = true;
				}

				if (MouseCoordinates.x >= about.get_position().x &&
					MouseCoordinates.x < 610 &&
					MouseCoordinates.y >= about.get_position().y &&
					MouseCoordinates.y < 660) {
					//std::cout << "Exit\n";
					//m_isDone = true;
				}

				if (MouseCoordinates.x >= exit.get_position().x &&
					MouseCoordinates.x < 1060 &&
					MouseCoordinates.y >= exit.get_position().y &&
					MouseCoordinates.y < 660) {
					//std::cout << "Exit\n";
					m_isDone = true;
				}

			}

			}
		}
	}
}
