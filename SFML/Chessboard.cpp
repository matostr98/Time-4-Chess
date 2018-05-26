#include "Chessboard.h"


void Chessboard::Sprites() {
	

	/*if (b_texture.loadFromFile("Pionek.png"))
		blue.setTexture(b_texture); else std::cout << "why?\n";

	if (g_texture.loadFromFile("high.png"))
		green.setTexture(g_texture); else std::cout << "why?\n";

	if (r_texture.loadFromFile("capt.png"))
		red.setTexture(r_texture); else std::cout << "why?\n";*/

	sf::Texture temp;
	
	//White
	if (temp.loadFromFile("wP.png"))
		TextureMap["wP"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wR.png"))
		TextureMap["wR"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wKn.png"))
		TextureMap["wKn"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wB.png"))
		TextureMap["wB"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wQ.png"))
		TextureMap["wQ"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wK.png"))
		TextureMap["wK"]=temp; else std::cout << "why?\n";
	
	//Black
	if (temp.loadFromFile("bP.png"))
		TextureMap["bP"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bR.png"))
		TextureMap["bR"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bKn.png"))
		TextureMap["bKn"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bB.png"))
		TextureMap["bB"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bQ.png"))
		TextureMap["bQ"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bK.png"))
		TextureMap["bK"]=temp; else std::cout << "why?\n";

	//Other
	if (temp.loadFromFile("blue.png"))
		TextureMap["blue"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("green.png"))
		TextureMap["green"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("red.png"))
		TextureMap["red"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("none.png"))
		TextureMap["none"] = temp; else std::cout << "why?\n";



	if (t_background.loadFromFile("Chessboard.png"))
		background.setTexture(t_background); else std::cout << "why?\n";

	//if (b_texture.loadFromFile("Pionek.png"))
	//	blue.setTexture(b_texture); else std::cout << "why?\n";

	//if (g_texture.loadFromFile("high.png"))
	//	green.setTexture(g_texture); else std::cout << "why?\n";

	//if (r_texture.loadFromFile("capt.png"))
	//	red.setTexture(r_texture); else std::cout << "why?\n";
}

Chessboard::Chessboard() {
	Sprites();
	Initialize();
}
Chessboard::~Chessboard() {}

void Chessboard::Move(sf::Vector2i ActiveCoord, sf::Vector2i CurrentCoord){

}

void Chessboard::ShowPossibleMoves(sf::Vector2i ActiveCoord){
	/*Board[ActiveCoord.x][ActiveCoord.y].piece->setPosition(ActiveCoord);
	std::vector<sf::Vector2i> posMoves{ Board[ActiveCoord.x][ActiveCoord.y].piece->getPossibleMoves() };
	for (auto e : posMoves) {
		Board[e.x][e.y].status = BoardStatus::Highlighted;

		sf::Sprite temp;
		temp.setTexture(TextureMap["green"]);

		temp.setPosition(24 + e.x * 84, 24 + e.y * 84);
		Board[e.x][e.y].StatRect = temp;*/

	switch (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceID()) {
		
		case PieceID::Pawn: { //Pawn move and collisions
			if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {
				if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {
					
					//two step move
					if (Board[ActiveCoord.x][ActiveCoord.y - 1].status == BoardStatus::Empty) {

						//for move one in two step move
						Board[ActiveCoord.x][ActiveCoord.y - 1].status = BoardStatus::Highlighted;
						Board[ActiveCoord.x][ActiveCoord.y - 1].StatRect = 
							StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 1].status, 
								{ ActiveCoord.x,  ActiveCoord.y - 1});

							if (Board[ActiveCoord.x][ActiveCoord.y - 2].status == BoardStatus::Empty) {

								//for move two in two step move
								Board[ActiveCoord.x][ActiveCoord.y - 2].status = BoardStatus::Highlighted;
								Board[ActiveCoord.x][ActiveCoord.y - 2].StatRect =
									StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 2].status,
										{ ActiveCoord.x,  ActiveCoord.y - 2 });
							}
					}
					//if capture
					
				}

				else {
				}
			}
			else {
				if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {
					//two step move

					if (Board[ActiveCoord.x][ActiveCoord.y + 1].status == BoardStatus::Empty) {

						//for move one in two step move
						Board[ActiveCoord.x][ActiveCoord.y + 1].status = BoardStatus::Highlighted;
						Board[ActiveCoord.x][ActiveCoord.y + 1].StatRect =
							StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 1 ].status,
								{ ActiveCoord.x,  ActiveCoord.y + 1 });

						if (Board[ActiveCoord.x][ActiveCoord.y + 2].status == BoardStatus::Empty) {

							//for move two in two step move
							Board[ActiveCoord.x][ActiveCoord.y + 2].status = BoardStatus::Highlighted;
							Board[ActiveCoord.x][ActiveCoord.y + 2].StatRect =
								StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 2].status,
									{ ActiveCoord.x,  ActiveCoord.y + 2 });
						}


					}

				}
			}
			break;
		}
	}
	//}
}

BoardStatus Chessboard::getBoardStatus(sf::Vector2i coor) {
	return Board[coor.x][coor.y].status;
}

void Chessboard::MakeActiveSprite(sf::Vector2i coord) {
	//sf::Sprite temp;
	//temp.setTexture(TextureMap["blue"]);

	//temp.setPosition(24 + coord.x * 84, 24 + coord.y * 84);
	Board[coord.x][coord.y].status = BoardStatus::Active;
	Board[coord.x][coord.y].StatRect = StatusSpriteHandler(Board[coord.x][coord.y].status, coord);
	ShowPossibleMoves(coord);
}

void Chessboard::UnmakeActiveSprite(sf::Vector2i coord) {
	//sf::Sprite temp;
	//temp.setTexture(TextureMap["none"]);


	//temp.setPosition(24 + coord.x * 84, 24 + coord.y * 84);
	Board[coord.x][coord.y].status = BoardStatus::Occupied;
	Board[coord.x][coord.y].StatRect = StatusSpriteHandler(Board[coord.x][coord.y].status, coord);
}

sf::Sprite Chessboard::StatusSpriteHandler(BoardStatus status, sf::Vector2i coord)
{
	sf::Sprite temp;

	//case
	switch (status) {
	case BoardStatus::Empty: { temp.setTexture(TextureMap["none"]); break; }
	case BoardStatus::Occupied: { temp.setTexture(TextureMap["none"]); break; }
	case BoardStatus::Highlighted: { temp.setTexture(TextureMap["green"]); break; }
	case BoardStatus::Active: { temp.setTexture(TextureMap["blue"]); break; }
	case BoardStatus::Capture: { temp.setTexture(TextureMap["red"]); break; }
	}

	temp.setPosition(24 + coord.x * 84, 24 + coord.y * 84);
	return temp;
}

sf::Sprite Chessboard::PieceSpriteHandler(PieceID id, PieceColor color, sf::Vector2i coord)
{
	sf::Sprite temp;
	if (color == PieceColor::White) {
		switch (id) {
		case PieceID::Pawn: {temp.setTexture(TextureMap["wP"]); break; }
		case PieceID::Rook: {temp.setTexture(TextureMap["wR"]); break; }
		case PieceID::Knight: {temp.setTexture(TextureMap["wKn"]); break; }
		case PieceID::Bishop: {temp.setTexture(TextureMap["wB"]); break; }
		case PieceID::Queen: {temp.setTexture(TextureMap["wQ"]); break; }
		case PieceID::King: {temp.setTexture(TextureMap["wK"]); break; }
		}
	}
	else {
		switch (id) {
		case PieceID::Pawn: {temp.setTexture(TextureMap["bP"]); break; }
		case PieceID::Rook: {temp.setTexture(TextureMap["bR"]); break; }
		case PieceID::Knight: {temp.setTexture(TextureMap["bKn"]); break; }
		case PieceID::Bishop: {temp.setTexture(TextureMap["bB"]); break; }
		case PieceID::Queen: {temp.setTexture(TextureMap["bQ"]); break; }
		case PieceID::King: {temp.setTexture(TextureMap["bK"]); break; }
		}
	}
	temp.setPosition(24 + coord.x * 84, 24 + coord.y * 84);
	return temp;
}

void Chessboard::Initialize() {
	//initialize board status


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			//gdzies tu pojawil sie blad przy wychodzeniu z aplikacji
			ChessPiece p(PieceColor::Black, PieceID::Pawn ,{i, j}, "bP");
			BlackPiecesSet.emplace_back(&p);
			Board[i][j].piece = std::make_shared<ChessPiece>(p); //ciekawe czy dobrze dziala
			Board[i][j].status = BoardStatus::Occupied;
			//sf::Sprite temp;
			//temp.setTexture(TextureMap[Board[i][j].piece->getSpriteName()]);
			//temp.setPosition(23 + i * 84, 23 + j * 84);
			Board[i][j].rect = PieceSpriteHandler(Board[i][j].piece->getPieceID(),
				Board[i][j].piece->getPieceColor(), {i, j});
			


		}
		for (int j = 2; j < 6; j++) {
			Board[i][j].status = BoardStatus::Empty;
			Board[i][j].piece = nullptr;
		}
		for (int j = 6; j < 8; j++) {
			ChessPiece p(PieceColor::White, PieceID::Pawn, { i, j }, "wP");
			BlackPiecesSet.emplace_back(&p);
			Board[i][j].piece = std::make_shared<ChessPiece>(p); //ciekawe czy dobrze dziala
			Board[i][j].status = BoardStatus::Occupied;
			//sf::Sprite temp;
			//temp.setTexture(TextureMap[Board[i][j].piece->getSpriteName()]);
			//temp.setPosition(23 + i * 84, 23 + j * 84);
			Board[i][j].rect = PieceSpriteHandler(Board[i][j].piece->getPieceID(),
				Board[i][j].piece->getPieceColor(), { i, j });
		}
	}
}

void Chessboard::Render(sf::RenderWindow & l_window) {

	l_window.draw(background);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].status != BoardStatus::Empty) {
				l_window.draw(Board[i][j].rect);
				l_window.draw(Board[i][j].StatRect);
			}
		}
	}

}