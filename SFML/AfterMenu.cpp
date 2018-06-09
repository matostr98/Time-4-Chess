#include "AfterMenu.h"


AfterMenu::AfterMenu() {/* Setup("Window", sf::Vector2u(700, 400));*/ }
AfterMenu::AfterMenu(const std::string& title, const sf::Vector2u& size) { Setup(title, size); }
AfterMenu::~AfterMenu() { Destroy(); }

void AfterMenu::Setup(const std::string title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	minimize = false;
	ngame = false;
	m_window.setFramerateLimit(60);

	font.loadFromFile("Assets/Fonts/CutiveMono-Regular.ttf");

	text.setString(m_windowTitle);
	text.setFont(font);
	text.setCharacterSize(84);
	text.setStyle(sf::Text::Bold);
	
	//std::cout << text.getGlobalBounds().width / 2 << ", " << text.getGlobalBounds().height / 2 << std::endl;
	text.setOrigin({ text.getGlobalBounds().width/2, text.getGlobalBounds().height/2 });
	
	text.setPosition(350, 85); 
	
	text.setFillColor(sf::Color::White);
	
	Create();
	Textures();
}

void AfterMenu::Setup() {
	m_isDone = false;
	minimize = false;
	ngame = false;
	m_window.setFramerateLimit(60);
}

void AfterMenu::Create() {
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, sf::Style::Titlebar);
}

void AfterMenu::Destroy() {
	m_window.close();
}

void AfterMenu::Textures() {
	texture.loadFromFile("Assets/Textures/Menus/m_window.png");
	background.setTexture(texture);

	exit.Setup({ 30, 290 }, "Assets/Textures/Buttons/sb_exit.png");
	board.Setup({ 250, 290 }, "Assets/Textures/Buttons/sb_board.png");
	newGame.Setup({ 470, 290 }, "Assets/Textures/Buttons/sb_new.png");
	
}

void AfterMenu::BeginDraw() { m_window.clear(sf::Color::Black); }
void AfterMenu::EndDraw() { m_window.display(); }

bool AfterMenu::IsDone() { return m_isDone; }

void AfterMenu::Draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}

void AfterMenu::Render() {
	BeginDraw();
	m_window.draw(background);
	m_window.draw(text);
	exit.DrawButton(m_window);
	board.DrawButton(m_window);
	newGame.DrawButton(m_window);
	EndDraw();
}

sf::Vector2u AfterMenu::GetWindowSize() { return m_windowSize; }



void AfterMenu::Update() {

	sf::Event event;
	while (m_window.pollEvent(event)) {

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

				/*if (MouseCoordinates.x>=exit.get_position().x &&
					MouseCoordinates.x < exit.get_position().x+ exit.get_dimensions().x &&
					MouseCoordinates.y >= exit.get_position().y &&
					MouseCoordinates.y < exit.get_position().y + exit.get_dimensions().y)*/ 
				
				if (MouseCoordinates.x >= exit.get_position().x &&
					MouseCoordinates.x < 230 &&
					MouseCoordinates.y >= exit.get_position().y &&
					MouseCoordinates.y < 350) {
					//std::cout << "Exit\n";
					m_isDone = true;
				}

				if (MouseCoordinates.x >= board.get_position().x &&
					MouseCoordinates.x < 450 &&
					MouseCoordinates.y >= board.get_position().y &&
					MouseCoordinates.y < 350) {
					std::cout << "Board\n";
					
					minimize = true;

				}

				if (MouseCoordinates.x >= newGame.get_position().x &&
					MouseCoordinates.x < 670 &&
					MouseCoordinates.y >= newGame.get_position().y &&
					MouseCoordinates.y < 350) {
					std::cout << "NewGame\n";

					ngame = true;

				}

			}
			}
		}
	}
}