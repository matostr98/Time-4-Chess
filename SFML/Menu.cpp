#include "Menu.h"



Menu::Menu() { Setup("Time-4-Chess", sf::Vector2u(1280, 720)); }
Menu::Menu(const std::string& title, const sf::Vector2u& size) { Setup(title, size); }
Menu::~Menu() { Destroy(); }

void Menu::Setup(const std::string title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	main = true;
	m_window.setFramerateLimit(60);
	timer = 900;
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
	
	sf::Texture temp;

	temp.loadFromFile("Assets/Textures/Menus/m_main.png");
	TextureMap["background"] = temp;

	temp.loadFromFile("Assets/Textures/Menus/m_credits.png");
	TextureMap["credits"] = temp;

	temp.loadFromFile("Assets/Textures/Menus/m_guide.png");
	TextureMap["guide"] = temp;

	temp.loadFromFile("Assets/Textures/Menus/m_options.png");
	TextureMap["options"] = temp;

	
	background.setTexture(TextureMap["background"]);
	
	m_credits.setTexture(TextureMap["credits"]);
	
	m_guide.setTexture(TextureMap["guide"]);
	
	m_options.setTexture(TextureMap["options"]);


	newGame.Setup({ 220, 270 }, "Assets/Textures/Buttons/bb_play.png");
	online.Setup({ 670, 270 }, "Assets/Textures/Buttons/bb_online.png");
	options.Setup({ 220, 410 }, "Assets/Textures/Buttons/bb_options.png");
	guide.Setup({ 670, 410 }, "Assets/Textures/Buttons/bb_guide.png");
	about.Setup({ 220, 550 }, "Assets/Textures/Buttons/bb_credits.png");
	exit.Setup({ 670, 550 }, "Assets/Textures/Buttons/bb_exit.png");
	back.Setup({ 1040, 640 }, "Assets/Textures/Buttons/sb_back.png");

	t3.Setup({185, 300}, "Assets/Textures/Buttons/o_3.png");
	t5.Setup({ 320, 300 }, "Assets/Textures/Buttons/o_5.png");
	t10.Setup({ 455, 300 }, "Assets/Textures/Buttons/o_10.png");
	t15.Setup({ 590, 300 }, "Assets/Textures/Buttons/o_15.png");
	t20.Setup({ 725, 300 }, "Assets/Textures/Buttons/o_20.png");
	t30.Setup({ 860, 300 }, "Assets/Textures/Buttons/o_30.png");
	t45.Setup({ 995, 300 }, "Assets/Textures/Buttons/o_45.png");
	t60.Setup({ 523, 430 }, "Assets/Textures/Buttons/o_60.png");
	t90.Setup({ 657, 430 }, "Assets/Textures/Buttons/o_90.png");

}


void Menu::BeginDraw() { m_window.clear(sf::Color::Black); }
void Menu::EndDraw() { m_window.display(); }

bool Menu::IsDone() { return m_isDone; }

void Menu::Draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}

void Menu::Render() {
	BeginDraw();

	if (main==true) {
		m_window.draw(background);
		online.DrawButton(m_window);
		options.DrawButton(m_window);
		guide.DrawButton(m_window);
		about.DrawButton(m_window);
		exit.DrawButton(m_window);
		newGame.DrawButton(m_window);
	}

	if (cabout==true) {
		m_window.draw(m_credits);
		back.DrawButton(m_window);
	}

	if (cguide == true) {
		m_window.draw(m_guide);
		back.DrawButton(m_window);
	}

	if (coptions == true) {
		m_window.draw(m_options);
		back.DrawButton(m_window);

		t3.DrawButton(m_window);
		t5.DrawButton(m_window);
		t10.DrawButton(m_window);
		t15.DrawButton(m_window);
		t20.DrawButton(m_window);
		t30.DrawButton(m_window);
		t45.DrawButton(m_window);
		t60.DrawButton(m_window);
		t90.DrawButton(m_window);
	}
	

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
			}
		case sf::Event::MouseButtonPressed:
			switch (event.key.code) {

			case sf::Mouse::Left: {
				//if left button is clicked
				sf::Vector2i MouseCoordinates = sf::Mouse::getPosition(m_window);


				if (main==true) {
					if (MouseCoordinates.x >= newGame.get_position().x &&
						MouseCoordinates.x < 610 &&
						MouseCoordinates.y >= newGame.get_position().y &&
						MouseCoordinates.y < 380) {
						
						cplay = true;
						main = false;
					}

					if (MouseCoordinates.x >= online.get_position().x &&
						MouseCoordinates.x < 1060 &&
						MouseCoordinates.y >= online.get_position().y &&
						MouseCoordinates.y < 380) {
						//m_isDone = true;
					}

					if (MouseCoordinates.x >= options.get_position().x &&
						MouseCoordinates.x < 610 &&
						MouseCoordinates.y >= options.get_position().y &&
						MouseCoordinates.y < 520) {
						coptions = true;
						main = false;
					}

					if (MouseCoordinates.x >= guide.get_position().x &&
						MouseCoordinates.x < 1060 &&
						MouseCoordinates.y >= guide.get_position().y &&
						MouseCoordinates.y < 520) {
						cguide = true;
						main = false;
					}

					if (MouseCoordinates.x >= about.get_position().x &&
						MouseCoordinates.x < 610 &&
						MouseCoordinates.y >= about.get_position().y &&
						MouseCoordinates.y < 660) {
						cabout = true;
						main = false;
					}

					if (MouseCoordinates.x >= exit.get_position().x &&
						MouseCoordinates.x < 1060 &&
						MouseCoordinates.y >= exit.get_position().y &&
						MouseCoordinates.y < 660) {
						//std::cout << "Exit\n";
						m_isDone = true;
					}
				}


				if (cabout == true) {
					if (MouseCoordinates.x >= back.get_position().x &&
						MouseCoordinates.x < 1240 &&
						MouseCoordinates.y >= back.get_position().y &&
						MouseCoordinates.y < 700) {
						main = true;
						cabout = false;
					}
				}

				if (cguide == true) {
					if (MouseCoordinates.x >= back.get_position().x &&
						MouseCoordinates.x < 1240 &&
						MouseCoordinates.y >= back.get_position().y &&
						MouseCoordinates.y < 700) {
						main = true;
						cguide = false;
					}
				}
				
				if (coptions == true) {
					if (MouseCoordinates.x >= back.get_position().x &&
						MouseCoordinates.x < 1240 &&
						MouseCoordinates.y >= back.get_position().y &&
						MouseCoordinates.y < 700) {
						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t3.get_position().x &&
						MouseCoordinates.x < 285 &&
						MouseCoordinates.y >= t3.get_position().y &&
						MouseCoordinates.y < 400) {
						timer = 180;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t5.get_position().x &&
						MouseCoordinates.x < 420 &&
						MouseCoordinates.y >= t5.get_position().y &&
						MouseCoordinates.y < 400) {
						timer = 300;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t10.get_position().x &&
						MouseCoordinates.x < 555 &&
						MouseCoordinates.y >= t10.get_position().y &&
						MouseCoordinates.y < 400) {
						timer = 600;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t15.get_position().x &&
						MouseCoordinates.x < 285 &&
						MouseCoordinates.y >= t15.get_position().y &&
						MouseCoordinates.y < 400) {
						timer = 900;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t20.get_position().x &&
						MouseCoordinates.x < 825 &&
						MouseCoordinates.y >= t20.get_position().y &&
						MouseCoordinates.y < 400) {
						timer = 1'200;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t30.get_position().x &&
						MouseCoordinates.x < 960 &&
						MouseCoordinates.y >= t30.get_position().y &&
						MouseCoordinates.y < 400) {
						timer = 1'800;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t45.get_position().x &&
						MouseCoordinates.x < 1095 &&
						MouseCoordinates.y >= t45.get_position().y &&
						MouseCoordinates.y < 400) {
						timer = 2'700;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t60.get_position().x &&
						MouseCoordinates.x < 623 &&
						MouseCoordinates.y >= t60.get_position().y &&
						MouseCoordinates.y < 530) {
						timer = 3'600;

						main = true;
						coptions = false;
					}

					if (MouseCoordinates.x >= t90.get_position().x &&
						MouseCoordinates.x < 757 &&
						MouseCoordinates.y >= t90.get_position().y &&
						MouseCoordinates.y < 530) {
						timer = 5'400;

						main = true;
						coptions = false;
					}
				}
			}

			}
		}
	}
}
