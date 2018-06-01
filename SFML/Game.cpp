#include "Game.h"

void Game::Setup(const std::string title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	playerTurn = PieceColor::White;
	Active = false;
	promotion = false;
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
					sf::Vector2i TempCoordinates = sf::Mouse::getPosition(m_window);
					

					//promotion

					if (promotion == true && TempCoordinates.x > 832 && TempCoordinates.x < 1168 
						&& TempCoordinates.y>318 && TempCoordinates.y < 402) {

						std::cout << "PromotionCoordinates: " << PromotionCoordinates.x << ", "
							<< PromotionCoordinates.y << std::endl;

						PromotionHandler(PromotionCoordinates.y == 0 ? 
							PieceColor::White : PieceColor::Black, TempCoordinates, PromotionCoordinates);

						//potem zmaiana stanu na bazowy i zmiana tury, ktora nie wejdzie bo promotion bylo true
						promotion = false;
						ActiveCoord = { -1, -1 };
						Active = false;
						playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
							: playerTurn = PieceColor::White;

					}

					//TODO mate				

					//if active is false, first click------------------------------------

					if (CurrentCoordinates.x >= 0 && CurrentCoordinates.x < 8
						&& CurrentCoordinates.y >= 0 && CurrentCoordinates.x < 8) {
						if (Active == false) {

							if (mate == true) {

								if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied
									&&m_chessboard.getPieceID(CurrentCoordinates) == PieceID::King) {

									Active = true;
									ActiveCoord = CurrentCoordinates;
									m_chessboard.MakeActiveSprite(ActiveCoord);
								}
							}		
							if (playerTurn == PieceColor::White && mate==false) {

					
								if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied
									&&m_chessboard.getPieceColor(CurrentCoordinates)==PieceColor::White) {
									
									Active = true;
									ActiveCoord = CurrentCoordinates;
									m_chessboard.MakeActiveSprite(ActiveCoord);
								}
							}
							else if (playerTurn == PieceColor::Black && mate == false) {
								if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied
									&&m_chessboard.getPieceColor(CurrentCoordinates) == PieceColor::Black) {
									
									Active = true;
									ActiveCoord = CurrentCoordinates;
									m_chessboard.MakeActiveSprite(ActiveCoord);
								}
							}
						} 
						
						//unmake active, second click------------------------------------

						else if (Active == true && CurrentCoordinates == ActiveCoord 
							&& promotion==false) {
							m_chessboard.UnmakeActiveSprite(ActiveCoord);
							ActiveCoord = { -1, -1 };
							Active = false;
						} 
						
						//move and capture, second click------------------------------------

						else if (Active == true && CurrentCoordinates != ActiveCoord
							&& promotion == false) {

							//move----------------------------
							if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Highlighted) {

								if (m_chessboard.getPieceID(ActiveCoord) == PieceID::King &&
									m_chessboard.getPieceID(CurrentCoordinates) == PieceID::Rook){
									
									m_chessboard.UnmakeActiveSprite(ActiveCoord);
									m_chessboard.ShortCastle(m_chessboard.getPieceColor(ActiveCoord));
								}
								else {
									m_chessboard.UnmakeActiveSprite(ActiveCoord);
									m_chessboard.Move(ActiveCoord, CurrentCoordinates);
								}

								

								if (mate == true) mate = false;

								//Check for mate
								if (m_chessboard.CheckForCheck()) {
									if (m_chessboard.CheckForCheckmate()) 
										m_isDone = true; 
									else mate = true;
								}

								//Check for promotion
								if ((CurrentCoordinates.y == 0 || CurrentCoordinates.y == 7) &&
									m_chessboard.getBoardStatus(CurrentCoordinates)==BoardStatus::Occupied &&
									m_chessboard.getPieceID(CurrentCoordinates) == PieceID::Pawn) {
									//m_chessboard.Promotion(PieceID::Queen, CurrentCoordinates);

									promotion = true;
								
									m_chessboard.RenderPromotion(
										CurrentCoordinates.y == 0 ? PieceColor::White : PieceColor::Black);
									
									PromotionCoordinates = CurrentCoordinates;
								}
								
								if (promotion == false) {
								playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
									: playerTurn = PieceColor::White;

									ActiveCoord = { -1, -1 };
									Active = false;
								}

							} 
							
							//capture-------------------------
							else if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Capture
								&& promotion == false) {

								m_chessboard.UnmakeActiveSprite(ActiveCoord);
								m_chessboard.Capture(ActiveCoord, CurrentCoordinates);

								if (mate == true) mate = false;

								//Check for mate
								if (m_chessboard.CheckForCheck()) {
									if (m_chessboard.CheckForCheckmate()) 
										m_isDone = true;
									else mate = true;
								}

								//Check for promotion
								if ((CurrentCoordinates.y == 0 || CurrentCoordinates.y == 7) &&
									m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied &&
									m_chessboard.getPieceID(CurrentCoordinates) == PieceID::Pawn) {

									promotion = true;
									m_chessboard.RenderPromotion(CurrentCoordinates.y == 0 ?
										 PieceColor::White : PieceColor::Black);

									PromotionCoordinates = CurrentCoordinates;
								}

								if (promotion == false) {
									playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
										: playerTurn = PieceColor::White;

									ActiveCoord = { -1, -1 };
									Active = false;
								}


							}

							//if z promocja, bo moze zadziala wtedy z kliknieciem
						}
					} 
					break;
				}
			}
		}
	}
}


int Game::GetCellNumber(sf::RenderWindow& l_window) {

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	if (mousePos.x > 23 && mousePos.x < 696 && mousePos.y>23 && mousePos.y < 695) {
		int column = (mousePos.x - 23) / cellSize;
		int row = (mousePos.y - 23) / cellSize;

		return column + row * 8;

	}
	else return -1;

}

sf::Vector2i Game::GetCellCoor()
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

		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Capture) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Capture: " << x << "," << y << "\n";
		}

		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Highlighted) {
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

PieceID Game::getPromotionPiece(sf::Vector2i mousePos)
{
	//sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	//if (mousePos.x > 832 && mousePos.x < 1168 && mousePos.y>318 && mousePos.y < 402) {
		switch ((mousePos.x - 832) / 84) {
		case 0: {return PieceID::Rook; break; }
		case 1: {return PieceID::Knight; break; }
		case 2: {return PieceID::Bishop; break; }
		case 3: {return PieceID::Queen; break; }
		//default: {return PieceID::Pawn; break; }
		}
	//}
	
}

void Game::PromotionHandler(PieceColor color, sf::Vector2i TempCoordinates, sf::Vector2i CurrentCoordinates){
	
	PieceID prom = getPromotionPiece(TempCoordinates);
	m_chessboard.Promotion(prom, CurrentCoordinates);


}


Game::Game() { Setup("T4C", sf::Vector2u(1280, 720)); }
Game::Game(const std::string& title, const sf::Vector2u& size) :m_chessboard() { Setup(title, size); }

Game::~Game() {}


//not used
void Game::HandleInput() {
}


void Game::Render() {
	BeginDraw();
	// Render here.
	m_chessboard.Render(m_window);

	EndDraw();
}


