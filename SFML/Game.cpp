#include "Game.h"

void Game::Setup(const std::string title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	playerTurn = 1;
	Active = false;
	Create();
}
void Game::Create() {
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle);

}
void Game::Destroy() {
	m_window.close();
}

void Game::BeginDraw() { m_window.clear(sf::Color::Black); }
void Game::EndDraw() { m_window.display(); }

bool Game::IsDone() { return m_isDone; }

sf::RenderWindow* Game::GetRenderWindow() { return &m_window; }
sf::Vector2u Game::GetWindowSize() { return m_windowSize; }

void Game::Update() {

	sf::Event event;
	while (m_window.pollEvent(event)) {

		switch (event.type) {
		case sf::Event::Closed: { m_isDone = true; break; }
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Escape: {m_isDone = true; break; }
			}
		case sf::Event::MouseButtonPressed:
			switch (event.key.code) {
			case sf::Mouse::Left: {
				//if left button is clicked

				OnClickTest();

				sf::Vector2i CurrentCoordinates = GetCellCoor();

				if (CurrentCoordinates.x >= 0 && CurrentCoordinates.x < 8 
					&& CurrentCoordinates.y >= 0 && CurrentCoordinates.x < 8)
					if (Active == false) {
						if (playerTurn == 1) {
							//na chwile obecna jest zle bo wymaja dobrej klasy ChessPiece
							if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied) {
								Active = true;
								ActiveCoord = CurrentCoordinates;
								m_chessboard.MakeActiveSprite(ActiveCoord);
								//m_chessboard.CallForPossibleMoves(ActiveCoord);
							}

						}
						else if (playerTurn == 2) {

						}
					}
					else if (Active == true && CurrentCoordinates == ActiveCoord) {
						m_chessboard.UnmakeActiveSprite(ActiveCoord);
						ActiveCoord = { -1, -1 };
						Active = false;
					}
					else if (Active == true && CurrentCoordinates != ActiveCoord) {
						if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Highlighted) {
							
							m_chessboard.UnmakeActiveSprite(ActiveCoord);
							m_chessboard.Move(ActiveCoord, CurrentCoordinates);

							
							ActiveCoord = { -1, -1 };
							Active = false;
						}
						else if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Capture) {
							//m_chessboard.Capture(ActiveCoord, CurrentCoordinates);

							m_chessboard.UnmakeActiveSprite(ActiveCoord);
							ActiveCoord = { -1, -1 };
							Active = false;
						}
					}

					break;
			}
			}
		}
		/*if (event.type == sf::Event::Closed) { m_isDone = true; }
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) { m_isDone = true; }*/

	}
}


int Game::GetCellNumber(sf::RenderWindow& l_window)
{



	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	if (mousePos.x > 23 && mousePos.x < 696 && mousePos.y>23 && mousePos.y < 695) {
		int column = (mousePos.x - 23) / cellSize;
		int row = (mousePos.y - 23) / cellSize;

		return column + row * 8;

	}
	else return -1;

}

sf::Vector2i Game::GetCellCoor(/*sf::RenderWindow& l_window*/)
{



	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	if (mousePos.x > 23 && mousePos.x < 696 && mousePos.y>23 && mousePos.y < 695) {
		int column = (mousePos.x - 23) / cellSize;
		int row = (mousePos.y - 23) / cellSize;

		return { column, row };

	}
	else return { -1, -1 };

}

void Game::OnClickTest() {
	if (GetCellCoor().x >= 0 && GetCellCoor().x < 8 && GetCellCoor().y >= 0 && GetCellCoor().x < 8) {
		if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Occupied) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Occupied: " << x << "," << y << "\n";

		}
		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Empty) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Empty: " << x << "," << y << "\n";
		}
		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Active) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Active: " << x << "," << y << "\n";
		}
		if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Highlighted) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Highlighted: " << x << "," << y << "\n";
		}
	}
	else {
		int x = GetCellCoor().x;
		int y = GetCellCoor().y;
		std::cout << "None: " << x << "," << y << "\n";
	}
}

Game::Game() { Setup("T4C", sf::Vector2u(1280, 720)); }
Game::Game(const std::string& title, const sf::Vector2u& size) :m_chessboard() { Setup(title, size); }

Game::~Game() {}



void Game::HandleInput() {
	// Input handling.
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Occupied) {
	std::cout<< "Occupied: " << GetCellNumber(m_window) << "\n";
	}
	else {
	std::cout << "Empty: " << GetCellNumber(m_window) << "\n";
	}
	}*/
}




void Game::Render() {
	BeginDraw();
	// Render here.
	m_chessboard.Render(m_window);

	EndDraw();
}


