#include "Chessboard.h"

void Chessboard::Sprites() {
	
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

}


void Chessboard::Sounds() {
	//sf::SoundBuffer temp;

	/*if (temp.loadFromFile("\Assets\SFX\Active.ogg")) 
		SFXMap["Active"] = temp; else std::cout << "Error!\n";

	if (temp.loadFromFile("\Assets\SFX\Move.ogg"))
		SFXMap["Move"] = temp; else std::cout << "Error!\n";

	if (temp.loadFromFile("\Assets\SFX\Capture.ogg"))
		SFXMap["Capture"] = temp; else std::cout << "Error!\n";*/


	/*if (temp.loadFromFile("\Assets\SFX\Active.ogg"))
		active.setBuffer(temp); else std::cout << "Error!\n";

	if (temp.loadFromFile("\Assets\SFX\Move.ogg"))
		move.setBuffer(temp); else std::cout << "Error!\n";

	if (temp.loadFromFile("\Assets\SFX\Capture.ogg"))
		capture.setBuffer(temp); else std::cout << "Error!\n";*/


}

void Chessboard::setPiece(PieceColor color, PieceID id, sf::Vector2i coord){
	ChessPiece p(color, id, coord);
	Board[coord.x][coord.y].piece = std::make_shared<ChessPiece>(p);
	Board[coord.x][coord.y].status = BoardStatus::Occupied;

	Board[coord.x][coord.y].rect = PieceSpriteHandler(Board[coord.x][coord.y].piece->getPieceID(),
		Board[coord.x][coord.y].piece->getPieceColor(), coord);
}

Chessboard::Chessboard() {
	Sprites();
	Sounds();
	Initialize();
}
Chessboard::~Chessboard() {}

//Move
void Chessboard::Move(sf::Vector2i ActiveCoord, sf::Vector2i NewCoord){
	//new field
	Board[NewCoord.x][NewCoord.y].piece = Board[ActiveCoord.x][ActiveCoord.y].piece;
	if (Board[NewCoord.x][NewCoord.y].piece->getPieceID() == PieceID::King) {
		Board[NewCoord.x][NewCoord.y].piece->getPieceColor() == PieceColor::White ?
			WhiteKingCoordinates = NewCoord : BlackKingCoordinates = NewCoord;
	}
	Board[NewCoord.x][NewCoord.y].piece->increamentMoveCount();

	PreviousCoordinates = ActiveCoord;

	Board[NewCoord.x][NewCoord.y].status = BoardStatus::Occupied;
	Board[NewCoord.x][NewCoord.y].rect = 
		PieceSpriteHandler(Board[NewCoord.x][NewCoord.y].piece->getPieceID(),
		Board[NewCoord.x][NewCoord.y].piece->getPieceColor(), NewCoord);
	Board[NewCoord.x][NewCoord.y].StatRect= 
		StatusSpriteHandler(Board[NewCoord.x][NewCoord.y].status, NewCoord);

	//old field
	Board[ActiveCoord.x][ActiveCoord.y].piece = nullptr;
	Board[ActiveCoord.x][ActiveCoord.y].status = BoardStatus::Empty;
	Board[ActiveCoord.x][ActiveCoord.y].rect= 
		StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);
	Board[ActiveCoord.x][ActiveCoord.y].StatRect =
		StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);

	
}
void Chessboard::Capture(sf::Vector2i ActiveCoord, sf::Vector2i NewCoord) {
	
	if (ActiveCoord.y == 3 || ActiveCoord.y == 4) {

		if (Board[NewCoord.x][ActiveCoord.y == 3 ? NewCoord.y : NewCoord.y ].piece == nullptr) {
			if (Board[NewCoord.x][ActiveCoord.y == 3 ? NewCoord.y + 1 : NewCoord.y - 1].piece->getPieceID() == PieceID::Pawn)
				
				EnPassant(ActiveCoord, NewCoord, ActiveCoord.y == 3 ? PieceColor::White : PieceColor::Black);
		}
		else {
			//opponent field (new field)
			Board[NewCoord.x][NewCoord.y].piece = nullptr;
			Board[NewCoord.x][NewCoord.y].piece = Board[ActiveCoord.x][ActiveCoord.y].piece;
			if (Board[NewCoord.x][NewCoord.y].piece->getPieceID() == PieceID::King) {
				Board[NewCoord.x][NewCoord.y].piece->getPieceColor() == PieceColor::White ?
					WhiteKingCoordinates = NewCoord : BlackKingCoordinates = NewCoord;
			}
			Board[NewCoord.x][NewCoord.y].piece->increamentMoveCount();
			PreviousCoordinates = ActiveCoord;

			Board[NewCoord.x][NewCoord.y].status = BoardStatus::Occupied;
			Board[NewCoord.x][NewCoord.y].rect =
				PieceSpriteHandler(Board[NewCoord.x][NewCoord.y].piece->getPieceID(),
					Board[NewCoord.x][NewCoord.y].piece->getPieceColor(), NewCoord);
			Board[NewCoord.x][NewCoord.y].StatRect =
				StatusSpriteHandler(Board[NewCoord.x][NewCoord.y].status, NewCoord);

			//old field
			Board[ActiveCoord.x][ActiveCoord.y].piece = nullptr;
			Board[ActiveCoord.x][ActiveCoord.y].status = BoardStatus::Empty;
			Board[ActiveCoord.x][ActiveCoord.y].rect =
				StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);
			Board[ActiveCoord.x][ActiveCoord.y].StatRect =
				StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);
		}

	}
	else {


		//opponent field (new field)
		Board[NewCoord.x][NewCoord.y].piece = nullptr;
		Board[NewCoord.x][NewCoord.y].piece = Board[ActiveCoord.x][ActiveCoord.y].piece;
		if (Board[NewCoord.x][NewCoord.y].piece->getPieceID() == PieceID::King) {
			Board[NewCoord.x][NewCoord.y].piece->getPieceColor() == PieceColor::White ?
				WhiteKingCoordinates = NewCoord : BlackKingCoordinates = NewCoord;
		}
		Board[NewCoord.x][NewCoord.y].piece->increamentMoveCount();
		PreviousCoordinates = ActiveCoord;

		Board[NewCoord.x][NewCoord.y].status = BoardStatus::Occupied;
		Board[NewCoord.x][NewCoord.y].rect =
			PieceSpriteHandler(Board[NewCoord.x][NewCoord.y].piece->getPieceID(),
				Board[NewCoord.x][NewCoord.y].piece->getPieceColor(), NewCoord);
		Board[NewCoord.x][NewCoord.y].StatRect =
			StatusSpriteHandler(Board[NewCoord.x][NewCoord.y].status, NewCoord);

		//old field
		Board[ActiveCoord.x][ActiveCoord.y].piece = nullptr;
		Board[ActiveCoord.x][ActiveCoord.y].status = BoardStatus::Empty;
		Board[ActiveCoord.x][ActiveCoord.y].rect =
			StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);
		Board[ActiveCoord.x][ActiveCoord.y].StatRect =
			StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);

	}
}

//Show moves--------------------------------------------------------------------
void Chessboard::ShowPossibleMoves(sf::Vector2i ActiveCoord){
	
	switch (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceID()) {
		
		case PieceID::Pawn: { //Show Pawn Move
			ShowPawnPossibleMoves(ActiveCoord);
			break;
		}
		case PieceID::Rook: { //Show Rook Move
			ShowRookPossibleMoves(ActiveCoord);
			break;
		}
		case PieceID::Knight: { //Show Knight Move
			ShowKnightPossibleMoves(ActiveCoord);
			break;
		}
		case PieceID::Bishop: { //Show Bishop Move
			ShowBishopPossibleMoves(ActiveCoord);
			break;
		}
		case PieceID::Queen: { //Show Queen Move
			ShowQueenPossibleMoves(ActiveCoord);
			break;
		}
		case PieceID::King: { //Show King Move
			ShowKingPossibleMoves(ActiveCoord);
			break;
		}
		

	}
}
void Chessboard::HidePossibleMoves(sf::Vector2i ActiveCoord) {
	switch (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceID()) {

	case PieceID::Pawn: { //Hide Pawn Move
		HidePawnPossibleMoves(ActiveCoord);
		break;
	}
	case PieceID::Rook: { //Hide Rook Move
		HideRookPossibleMoves(ActiveCoord);
		break;
	}
	case PieceID::Knight: { //Hide Knight Move
		HideKnightPossibleMoves(ActiveCoord);
		break;
	}
	case PieceID::Bishop: { //Hide Bishop Move
		HideBishopPossibleMoves(ActiveCoord);
		break;
	}
	case PieceID::Queen: { //Hide Queen Move
		HideQueenPossibleMoves(ActiveCoord);
		break;
	}
	case PieceID::King: { //Hide King Move
		HideKingPossibleMoves(ActiveCoord);
		break;
	}
	}
}


void Chessboard::Promotion(PieceID id, sf::Vector2i coord) {
		Board[coord.x][coord.y].piece->setPieceIDforPromotion(id);
		Board[coord.x][coord.y].rect = PieceSpriteHandler(Board[coord.x][coord.y].piece->getPieceID(),
			Board[coord.x][coord.y].piece->getPieceColor(), coord);
		promotion = false;
}

void Chessboard::ShortCastle(PieceColor color) {
	int i = 4;
	int j;
	color == PieceColor::White ? j = 7 : j = 0;

	Move({ i, j }, { i + 2, j });
	Move({ i + 3, j }, { i + 1, j });
	j == 7 ? WhiteCastle = true : BlackCastle = true;
	j == 7 ? WhiteKingCoordinates = { i + 2, j } : BlackKingCoordinates = { i + 2, j };
	Board[i + 3][j].status = BoardStatus::Empty;
	Board[i + 3][j].StatRect = StatusSpriteHandler(
		Board[i + 3][j].status, { i + 3, j });


}

void Chessboard::LongCastle(PieceColor color){
	int i = 4;
	int j;
	color == PieceColor::White ? j = 7 : j = 0;

	Move({ i, j }, { i - 2, j });
	Move({ i - 4, j }, { i - 1, j });
	j == 7 ? WhiteCastle = true : BlackCastle = true;
	j == 7 ? WhiteKingCoordinates = { i - 2, j } : BlackKingCoordinates = { i - 2, j };
	Board[i - 4][j].status = BoardStatus::Empty;
	Board[i - 4][j].StatRect = StatusSpriteHandler(
		Board[i - 4][j].status, { i - 4, j });

}

void Chessboard::EnPassant(sf::Vector2i ActiveCoord, sf::Vector2i NewCoord, PieceColor color){
	
	Move(ActiveCoord, NewCoord);
	Board[NewCoord.x][NewCoord.y].piece->increamentMoveCount();
	PreviousCoordinates = ActiveCoord;

	if (color == PieceColor::White) {

		

		//old field
		Board[NewCoord.x][NewCoord.y + 1].piece = nullptr;
		Board[NewCoord.x][NewCoord.y + 1].status = BoardStatus::Empty;
		Board[NewCoord.x][NewCoord.y + 1].rect =
			StatusSpriteHandler(Board[NewCoord.x][NewCoord.y + 1].status, { NewCoord.x, NewCoord.y + 1 });
		Board[NewCoord.x][NewCoord.y + 1].StatRect =
			StatusSpriteHandler(Board[NewCoord.x][NewCoord.y + 1].status, { NewCoord.x, NewCoord.y + 1 });


	}
	else {
		//old field
		Board[NewCoord.x][NewCoord.y - 1].piece = nullptr;
		Board[NewCoord.x][NewCoord.y - 1].status = BoardStatus::Empty;
		Board[NewCoord.x][NewCoord.y - 1].rect =
			StatusSpriteHandler(Board[NewCoord.x][NewCoord.y - 1].status, { NewCoord.x, NewCoord.y - 1 });
		Board[NewCoord.x][NewCoord.y - 1].StatRect =
			StatusSpriteHandler(Board[NewCoord.x][NewCoord.y - 1].status, { NewCoord.x, NewCoord.y - 1 });

	}

}

void Chessboard::ShowShortCastle(PieceColor color){
	int i = 4;
	int j;
	color == PieceColor::White ? j = 7 : j = 0;

	//Check move count
	if (Board[i][j].piece->getMoveCount() == 0 && Board[i + 3][j].piece->getMoveCount() == 0) {

		if (!CheckIfFieldIsAttacked({ i, j }, j == 7 ? PieceColor::White : PieceColor::Black)) {
			if (Board[i + 1][j].status==BoardStatus::Empty && 
				!CheckIfFieldIsAttacked({ i + 1, j }, j == 7 ? PieceColor::White : PieceColor::Black)) {
				if (Board[i + 2][j].status == BoardStatus::Empty &&
					!CheckIfFieldIsAttacked({ i + 2, j }, j == 7 ? PieceColor::White : PieceColor::Black)) {
					//TODO hide and move function for castle

					
						Board[i + 3][j].status = BoardStatus::Highlighted;
						Board[i + 3][j].StatRect = StatusSpriteHandler(
							Board[i + 3][j].status, { i + 3, j });
					

					//ChangeStatusForHighlighted(i + 3, j);
					//Board[i + 3][j].status = BoardStatus::Highlighted;
				}
			}
		}
	}
}

void Chessboard::ShowLongCastle(PieceColor color){
	int i = 4;
	int j;
	color == PieceColor::White ? j = 7 : j = 0;

	//Check move count
	if (Board[i][j].piece->getMoveCount() == 0 && Board[i - 4][j].piece->getMoveCount() == 0) {

		if (!CheckIfFieldIsAttacked({ i, j }, j == 7 ? PieceColor::White : PieceColor::Black)) {
			if (Board[i - 1][j].status == BoardStatus::Empty &&
				!CheckIfFieldIsAttacked({ i - 1, j }, j == 7 ? PieceColor::White : PieceColor::Black)) {
				if (Board[i - 2][j].status == BoardStatus::Empty &&
					!CheckIfFieldIsAttacked({ i - 2, j }, j == 7 ? PieceColor::White : PieceColor::Black)) {
					if (Board[i - 3][j].status == BoardStatus::Empty) {


						Board[i - 4][j].status = BoardStatus::Highlighted;
						Board[i - 4][j].StatRect = StatusSpriteHandler(
							Board[i - 4][j].status, { i - 4, j });
					}
				}
			}
		}
	}
}

//Function checking whether field is being attacked is not checked
bool Chessboard::CheckIfFieldIsAttacked(sf::Vector2i Coord, PieceColor color) {
	
	//Rook, Bishop and Queen

	int x = Coord.x;
	int y = Coord.y;
	//left---------------
	while (x - 1 >= 0 && x - 1 <= 7) {
		
		if (Board[x - 1][y].status == BoardStatus::Empty ||
			Board[x - 1][y].status == BoardStatus::Occupied) {

			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() != color) {
					if (Board[x - 1][y].piece->getPieceID() == PieceID::Rook ||
						Board[x - 1][y].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneRookAttack(color, { x - 1, y })) return true;
						return true;
					}
					else break;
				}
				else break;
			}
			else {
				if (CheckOneRookAttack(color, { x - 1, y })) return true;
			}
		}
		x--;
	}


	//right
	x = Coord.x;
	y = Coord.y;
	while (x + 1 >= 0 && x + 1 <= 7) {
		
		if (Board[x + 1][y].status == BoardStatus::Empty ||
			Board[x + 1][y].status == BoardStatus::Occupied) {

			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() != color) {
					if (Board[x + 1][y].piece->getPieceID() == PieceID::Rook ||
						Board[x + 1][y].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneRookAttack(color, { x - 1, y })) return true;
						return true;
					}
					else break;
				}
				else break;
			}
			else {
				//if (CheckOneRookAttack(color, { x + 1, y })) return true;
			}
		}

		x++;
	}

	//up
	x = Coord.x;
	y = Coord.y;
	while (y - 1 >= 0 && y - 1 <= 7) {
		
		if (Board[x][y - 1].status == BoardStatus::Empty ||
			Board[x][y - 1].status == BoardStatus::Occupied) {

			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() != color) {
					if (Board[x][y - 1].piece->getPieceID() == PieceID::Rook ||
						Board[x][y - 1].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneRookAttack(color, { x, y - 1 })) return true;
						return true;
					}
					else break;
				}
				else break;
			}
			else {
				//if (CheckOneRookAttack(color, { x, y - 1 })) return true;
			}
		}
		y--;

	}

	//down
	x = Coord.x;
	y = Coord.y;
	while (y + 1 >= 0 && y + 1 <= 7) {
		
		if (Board[x][y + 1].status == BoardStatus::Empty ||
			Board[x][y + 1].status == BoardStatus::Occupied) {

			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() != color) {
					if (Board[x][y + 1].piece->getPieceID() == PieceID::Rook ||
						Board[x][y + 1].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneRookAttack(color, { x, y + 1 })) 
							return true;
					}
					else break;
				}
				else break;
			}
			else {
				//if (CheckOneRookAttack(color, { x, y + 1 })) return true;
			}
		}
		
		y++;
	}


	//top-left---------------
	x = Coord.x;
	y = Coord.y;
	
	while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
		
		if (Board[x - 1][y - 1].status == BoardStatus::Empty ||
			Board[x - 1][y - 1].status == BoardStatus::Occupied) {

			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() != color) {
					if (Board[x - 1][y - 1].piece->getPieceID() == PieceID::Bishop ||
						Board[x - 1][y - 1].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneBishopAttack(color, { x - 1, y - 1 })) 
							return true;
					}
					else break;
				}
				else break;
			}
			else {
				//if (CheckOneBishopAttack(color, { x - 1, y - 1 })) return true;
			}
		}


		x--; y--;
	}

	//top-right---------------

	x = Coord.x;
	y = Coord.y;

	while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
		
		if (Board[x + 1][y - 1].status == BoardStatus::Empty ||
			Board[x + 1][y - 1].status == BoardStatus::Occupied) {

			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() != color) {
					if (Board[x + 1][y - 1].piece->getPieceID() == PieceID::Bishop ||
						Board[x + 1][y - 1].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneBishopAttack(color, { x + 1, y - 1 })) 
							return true;
					}
					else break;
				}
				else break;
			}
			else {
				//if (CheckOneBishopAttack(color, { x + 1, y - 1 })) return true;
			}
		}

		x++; y--;
	}

	//bottom-left---------------

	x = Coord.x;
	y = Coord.y;

	while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
		
		if (Board[x - 1][y + 1].status == BoardStatus::Empty ||
			Board[x - 1][y + 1].status == BoardStatus::Occupied) {

			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() != color) {
					if (Board[x - 1][y + 1].piece->getPieceID() == PieceID::Bishop ||
						Board[x - 1][y + 1].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneBishopAttack(color, { x - 1, y + 1 })) 
							return true;
					}
					else break;
				}
				else break;
			}
			else {
				//if (CheckOneBishopAttack(color, { x - 1, y + 1 })) return true;
			}
		}

		x--; y++;
	}

	//bottom-right---------------

	x = Coord.x;
	y = Coord.y;

	while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
		
		if (Board[x + 1][y + 1].status == BoardStatus::Empty ||
			Board[x + 1][y + 1].status == BoardStatus::Occupied) {

			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() != color) {
					if (Board[x + 1][y + 1].piece->getPieceID() == PieceID::Bishop ||
						Board[x + 1][y + 1].piece->getPieceID() == PieceID::Queen) {
						//if (CheckOneBishopAttack(color, { x + 1, y + 1 })) 
							return true;
					}
					else break;
				}
				else break;
			}
			else {
				//if (CheckOneBishopAttack(color, { x + 1, y + 1 })) return true;
			}
		}

		x++; y++;
	}


	//King and Pawn

	x = Coord.x;
	y = Coord.y;

	//left---------------
	if (x - 1 >= 0 && x - 1 <= 7) {
		if (Board[x - 1][y].status == BoardStatus::Occupied&&
			Board[x - 1][y].piece->getPieceColor() != color &&
			Board[x - 1][y].piece->getPieceID() == PieceID::King)
		//if (CheckOneKingAttack(color, { x - 1 , y})) 
			return true;
	}

	//right
	if (x + 1 >= 0 && x + 1 <= 7) {
		if (Board[x + 1][y].status == BoardStatus::Occupied&&
			Board[x + 1][y].piece->getPieceColor() != color &&
			Board[x + 1][y].piece->getPieceID() == PieceID::King)
		//if (CheckOneKingAttack(color, { x + 1 , y})) 
			return true;
	}

	//up
	if (y - 1 >= 0 && y - 1 <= 7) {
		if (Board[x][y - 1].status == BoardStatus::Occupied&&
			Board[x][y - 1].piece->getPieceColor() != color &&
			Board[x][y - 1].piece->getPieceID() == PieceID::King)
		//if (CheckOneKingAttack(color, { x , y - 1 })) 
			return true;
	}

	//down
	if (y + 1 >= 0 && y + 1 <= 7) {
		if (Board[x][y + 1].status == BoardStatus::Occupied&&
			Board[x][y + 1].piece->getPieceColor() != color &&
			Board[x][y + 1].piece->getPieceID() == PieceID::King)
		//if (CheckOneKingAttack(color, { x , y + 1 })) 
			return true;
	}

	//top-left---------------
	if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
		
		if (Board[x - 1][y - 1].status == BoardStatus::Occupied&&
			Board[x - 1][y - 1].piece->getPieceColor() != color) {

			if (Board[x - 1][y - 1].piece->getPieceID() == PieceID::King)
				//if (CheckOneKingAttack(color, { x - 1 , y - 1 })) 
				return true;

			if (Board[x - 1][y - 1].piece->getPieceID() == PieceID::Pawn)
				//if (CheckOnePawnAttack(color, { x - 1 , y - 1 })) 
				return true;
		}
	}


	//top-right---------------
	if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
		if (Board[x + 1][y - 1].status == BoardStatus::Occupied&&
			Board[x + 1][y - 1].piece->getPieceColor() != color) {

			if (Board[x + 1][y - 1].piece->getPieceID() == PieceID::King)
				//if (CheckOneKingAttack(color, { x + 1 , y - 1 })) 
					return true;

			if (Board[x + 1][y - 1].piece->getPieceID() == PieceID::Pawn)
				//if (CheckOnePawnAttack(color, { x + 1 , y - 1 })) 
				return true;
		}
	}

	//bottom-left---------------
	if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
		
		if (Board[x - 1][y + 1].status == BoardStatus::Occupied&&
			Board[x - 1][y + 1].piece->getPieceColor() != color) {

			if (Board[x - 1][y + 1].piece->getPieceID() == PieceID::King)
				//if (CheckOneKingAttack(color, { x - 1 , y + 1 })) 
				return true;

			if (Board[x - 1][y + 1].piece->getPieceID() == PieceID::Pawn)
				//if (CheckOnePawnAttack(color, { x - 1 , y + 1 })) 
				return true;
		}
	}

	//bottom-right---------------
	if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
		if (Board[x + 1][y + 1].status == BoardStatus::Occupied&&
			Board[x + 1][y + 1].piece->getPieceColor() != color) {

			if (Board[x + 1][y + 1].piece->getPieceID() == PieceID::King)
				//if (CheckOneKingAttack(color, { x + 1 , y + 1 })) 
				return true;

			if (Board[x + 1][y + 1].piece->getPieceID() == PieceID::Pawn)
				//if (CheckOnePawnAttack(color, { x + 1 , y + 1 })) 
				return true;
		}
	}

	//Knight

	x = Coord.x;
	y = Coord.y;



	//top - left----------------------
	if ((x - 1 >= 0 && y - 2 >= 0)) {		
		if (Board[x - 1][y - 2].status == BoardStatus::Occupied) {
			if (Board[x - 1][y - 2].piece->getPieceColor() != color) {
				if (Board[x - 1][y - 2].piece->getPieceID() == PieceID::Knight) return true;
			}
		}
	}

	//top - right----------------------
	if ((x + 1 <= 7 && y - 2 >= 0)) {

		if ((x + 1 >= 0 && y - 2 >= 0)) {
			if (Board[x + 1][y - 2].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 2].piece->getPieceColor() != color) {
					if (Board[x + 1][y - 2].piece->getPieceID() == PieceID::Knight) return true;
				}
			}
		}
	}

	//bottom - left----------------------
	if ((x - 1 >= 0 && y + 2 <= 7)) {

		if ((x - 1 >= 0 && y + 2 >= 0)) {
			if (Board[x - 1][y + 2].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 2].piece->getPieceColor() != color) {
					if (Board[x - 1][y + 2].piece->getPieceID() == PieceID::Knight) return true;
				}
			}
		}
	}

	//bottom - right----------------------
	if ((x + 1 <= 7 && y + 2 <= 7)) {

		if ((x + 1 >= 0 && y + 2 >= 0)) {
			if (Board[x + 1][y + 2].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 2].piece->getPieceColor() != color) {
					if (Board[x + 1][y + 2].piece->getPieceID() == PieceID::Knight) return true;
				}
			}
		}
	}



	//left - bottom----------------------
	if ((x - 2 >= 0 && y + 1 <= 7)) {

		if ((x - 2 >= 0 && y + 1 >= 0)) {
			if (Board[x - 2][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 2][y + 1].piece->getPieceColor() != color) {
					if (Board[x - 2][y + 1].piece->getPieceID() == PieceID::Knight) return true;
				}
			}
		}
	}

	//left - top----------------------
	if ((x - 2 >= 0 && y - 1 >= 0)) {

		if ((x - 2 >= 0 && y - 1 >= 0)) {
			if (Board[x - 2][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 2][y - 1].piece->getPieceColor() != color) {
					if (Board[x - 2][y - 1].piece->getPieceID() == PieceID::Knight) return true;
				}
			}
		}
	}

	//right - top------------------
	if ((x + 2 <= 7 && y + 1 <= 7)) {

		if ((x + 2 >= 0 && y + 1 >= 0)) {
			if (Board[x + 2][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 2][y + 1].piece->getPieceColor() != color) {
					if (Board[x + 2][y + 1].piece->getPieceID() == PieceID::Knight) return true;
				}
			}
		}
	}

	//right - bottom------------------
	if ((x + 2 <= 7 && y - 1 >= 0)) {

		if ((x + 2 >= 0 && y - 1 >= 0)) {
			if (Board[x + 2][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 2][y - 1].piece->getPieceColor() != color) {
					if (Board[x + 2][y - 1].piece->getPieceID() == PieceID::Knight) return true;
				}
			}
		}
	}



	return false;
}



bool Chessboard::CheckOneRookAttack(PieceColor color, sf::Vector2i Coord) {
	if (Board[Coord.x][Coord.y].status == BoardStatus::Occupied) {
		if (Board[Coord.x][Coord.y].piece->getPieceColor() != color) {
			if (Board[Coord.x][Coord.y].piece->getPieceID() == PieceID::Queen ||
				Board[Coord.x][Coord.y].piece->getPieceID() == PieceID::Rook) return true;
		}
		else return false;

	}
	else return false;
}
bool Chessboard::CheckOneBishopAttack(PieceColor color, sf::Vector2i Coord) {
	if (Board[Coord.x][Coord.y].status == BoardStatus::Occupied) {
		if (Board[Coord.x][Coord.y].piece->getPieceColor() != color) {
			if (Board[Coord.x][Coord.y].piece->getPieceID() == PieceID::Queen ||
				Board[Coord.x][Coord.y].piece->getPieceID() == PieceID::Bishop) return true;
		}
		else return false;

	}
	else return false;
}
bool Chessboard::CheckOneKnightAttack(PieceColor color, sf::Vector2i Coord) {
	if (Board[Coord.x][Coord.y].status == BoardStatus::Occupied) {
		if (Board[Coord.x][Coord.y].piece->getPieceColor() != color) {
			if (Board[Coord.x][Coord.y].piece->getPieceID() == PieceID::Knight) return true;
		}
		else return false;

	}
	else return false;
}
bool Chessboard::CheckOneKingAttack(PieceColor color, sf::Vector2i Coord) {
	//if (Board[Coord.x][Coord.y].status == BoardStatus::Occupied) {
		if (Board[Coord.x][Coord.y].piece->getPieceColor() != color) {
			if (Board[Coord.x][Coord.y].piece->getPieceID() == PieceID::King) return true;
		}
		else return false;

	//}
	//else return false;
}
bool Chessboard::CheckOnePawnAttack(PieceColor color, sf::Vector2i Coord) {
	//if (Board[Coord.x][Coord.y].status == BoardStatus::Occupied) {
		if (Board[Coord.x][Coord.y].piece->getPieceColor() != color) {
			if (Board[Coord.x][Coord.y].piece->getPieceID() == PieceID::Pawn) return true;
		}
		else return false;

	//}
	//else return false;
}


bool Chessboard::CheckForCheck(){
	if (CheckIfFieldIsAttacked(WhiteKingCoordinates, PieceColor::White)) {
		check = PieceColor::White;
		return true;
	}
	if (CheckIfFieldIsAttacked(BlackKingCoordinates, PieceColor::Black)) {
		check = PieceColor::Black;
		return true;
	}

	return false;
}

bool Chessboard::CheckForCheckmate()
{
	std::cout << "Black King Coordinates: " << BlackKingCoordinates.x << ", " << BlackKingCoordinates.y << std::endl;
	std::cout << "White King Coordinates: " << WhiteKingCoordinates.x << ", " << WhiteKingCoordinates.y << std::endl;


	if (check == PieceColor::White) {
	//left, right, top, bottom---------------------------------------------------------
		//left
		if (WhiteKingCoordinates.x - 1 >= 0 && WhiteKingCoordinates.x - 1 <= 7) {
			if (Board[WhiteKingCoordinates.x - 1][WhiteKingCoordinates.y].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x - 1, WhiteKingCoordinates.y }, check)) return false;
		}

		
		//right
		if (WhiteKingCoordinates.x + 1 >= 0 && WhiteKingCoordinates.x + 1 <= 7) {
			if (Board[WhiteKingCoordinates.x + 1][WhiteKingCoordinates.y].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x + 1, WhiteKingCoordinates.y }, check)) return false;
		}

		//top

		if (WhiteKingCoordinates.y + 1 >= 0 && WhiteKingCoordinates.y + 1 <= 7) {
			if (Board[WhiteKingCoordinates.x][WhiteKingCoordinates.y + 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x, WhiteKingCoordinates.y + 1 }, check)) return false;
		}


		//bottom
		if (WhiteKingCoordinates.y - 1 >= 0 && WhiteKingCoordinates.y - 1 <= 7) {
			if (Board[WhiteKingCoordinates.x][WhiteKingCoordinates.y - 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x, WhiteKingCoordinates.y - 1 }, check)) return false;
		}



		//diagonals-------------------------------------------------------------
		//top-left

		if  (WhiteKingCoordinates.x - 1 >= 0 && WhiteKingCoordinates.x - 1 <= 7 &&
			WhiteKingCoordinates.y - 1 >= 0 && WhiteKingCoordinates.y - 1 <= 7) {
			if (Board[WhiteKingCoordinates.x - 1][WhiteKingCoordinates.y - 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x - 1, WhiteKingCoordinates.y - 1 }, check)) return false;
		}
		

		//top-right
		if (WhiteKingCoordinates.x + 1 >= 0 && WhiteKingCoordinates.x + 1 <= 7 &&
			WhiteKingCoordinates.y - 1 >= 0 && WhiteKingCoordinates.y - 1 <= 7) {
			if (Board[WhiteKingCoordinates.x + 1][WhiteKingCoordinates.y - 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x + 1, WhiteKingCoordinates.y - 1 }, check)) return false;
		}

		//bottom-left
		if (WhiteKingCoordinates.x - 1 >= 0 && WhiteKingCoordinates.x - 1 <= 7 &&
			WhiteKingCoordinates.y + 1 >= 0 && WhiteKingCoordinates.y + 1 <= 7) {
			if (Board[WhiteKingCoordinates.x - 1][WhiteKingCoordinates.y + 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x - 1, WhiteKingCoordinates.y + 1 }, check)) return false;
		}

		//bottom-right
		if (WhiteKingCoordinates.x + 1 >= 0 && WhiteKingCoordinates.x + 1 <= 7 &&
			WhiteKingCoordinates.y + 1 >= 0 && WhiteKingCoordinates.y + 1 <= 7) {
			if (Board[WhiteKingCoordinates.x + 1][WhiteKingCoordinates.y + 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ WhiteKingCoordinates.x + 1, WhiteKingCoordinates.y + 1 }, check)) return false;
		}

	}
	else if (check==PieceColor::Black) {
		
		//left, right, top, bottom---------------------------------------------------------
		//left
		if (BlackKingCoordinates.x - 1 >= 0 && BlackKingCoordinates.x - 1 <= 7) {
			if (Board[BlackKingCoordinates.x - 1][BlackKingCoordinates.y].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x - 1, BlackKingCoordinates.y }, check)) return false;
		}


		//right
		if (BlackKingCoordinates.x + 1 >= 0 && BlackKingCoordinates.x + 1 <= 7) {
			if (Board[BlackKingCoordinates.x + 1][BlackKingCoordinates.y].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x + 1, BlackKingCoordinates.y }, check)) return false;
		}

		//top

		if (BlackKingCoordinates.y + 1 >= 0 && BlackKingCoordinates.y + 1 <= 7) {
			if (Board[BlackKingCoordinates.x][BlackKingCoordinates.y + 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x, BlackKingCoordinates.y + 1 }, check)) return false;
		}


		//bottom
		if (BlackKingCoordinates.y - 1 >= 0 && BlackKingCoordinates.y - 1 <= 7) {
			if (Board[BlackKingCoordinates.x][BlackKingCoordinates.y - 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x, BlackKingCoordinates.y - 1 }, check)) return false;
		}



		//diagonals-------------------------------------------------------------
		//top-left

		if (BlackKingCoordinates.x - 1 >= 0 && BlackKingCoordinates.x - 1 <= 7 &&
			BlackKingCoordinates.y - 1 >= 0 && BlackKingCoordinates.y - 1 <= 7) {
			if (Board[BlackKingCoordinates.x - 1][BlackKingCoordinates.y - 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x - 1, BlackKingCoordinates.y - 1 }, check)) return false;
		}


		//top-right
		if (BlackKingCoordinates.x + 1 >= 0 && BlackKingCoordinates.x + 1 <= 7 &&
			BlackKingCoordinates.y - 1 >= 0 && BlackKingCoordinates.y - 1 <= 7) {
			if (Board[BlackKingCoordinates.x + 1][BlackKingCoordinates.y - 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x + 1, BlackKingCoordinates.y - 1 }, check)) return false;
		}

		//bottom-left
		if (BlackKingCoordinates.x - 1 >= 0 && BlackKingCoordinates.x - 1 <= 7 &&
			BlackKingCoordinates.y + 1 >= 0 && BlackKingCoordinates.y + 1 <= 7) {
			if (Board[BlackKingCoordinates.x - 1][BlackKingCoordinates.y + 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x - 1, BlackKingCoordinates.y + 1 }, check)) return false;
		}

		//bottom-right
		if (BlackKingCoordinates.x + 1 >= 0 && BlackKingCoordinates.x + 1 <= 7 &&
			BlackKingCoordinates.y + 1 >= 0 && BlackKingCoordinates.y + 1 <= 7) {
			if (Board[BlackKingCoordinates.x + 1][BlackKingCoordinates.y + 1].status == BoardStatus::Empty)
				if (!CheckIfFieldIsAttacked({ BlackKingCoordinates.x + 1, BlackKingCoordinates.y + 1 }, check)) return false;
		}
	}
	return true;
}

BoardStatus Chessboard::getBoardStatus(sf::Vector2i coor) {
	return Board[coor.x][coor.y].status;
}

PieceColor Chessboard::getPieceColor(sf::Vector2i coor)
{
	return Board[coor.x][coor.y].piece->getPieceColor();	
}

PieceID Chessboard::getPieceID(sf::Vector2i coor)
{
	return Board[coor.x][coor.y].piece->getPieceID();
}

bool Chessboard::getNullPtr(sf::Vector2i coor){

	if (Board[coor.x][coor.y].piece == nullptr) return true;
	else return false;
}

void Chessboard::MakeActiveSprite(sf::Vector2i coord) {
	Board[coord.x][coord.y].status = BoardStatus::Active;
	Board[coord.x][coord.y].StatRect = StatusSpriteHandler(Board[coord.x][coord.y].status, coord);
	ShowPossibleMoves(coord);
}

//void Chessboard::MakeActiveKingSprite(sf::Vector2i Coord) {
//	Board[Coord.x][Coord.y].status = BoardStatus::Active;
//	Board[Coord.x][Coord.y].StatRect = StatusSpriteHandler(Board[Coord.x][Coord.y].status, Coord);
//	ShowPossibleMoves(Coord);
//}

void Chessboard::UnmakeActiveSprite(sf::Vector2i coord) {

	Board[coord.x][coord.y].status = BoardStatus::Occupied;
	Board[coord.x][coord.y].StatRect = StatusSpriteHandler(Board[coord.x][coord.y].status, coord);
	HidePossibleMoves(coord);
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
	else if (color == PieceColor::Black) {
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

sf::Sprite Chessboard::PromotionSpriteHandler(PieceColor color, int n) {
	sf::Sprite temp;
	std::cout << "PromotionSpriteHandler\n";
	
	if (color == PieceColor::White) {
		switch (n) {
		case 0: {temp.setTexture(TextureMap["wR"]); break; }
		case 1: {temp.setTexture(TextureMap["wKn"]); break; }
		case 2: {temp.setTexture(TextureMap["wB"]); break; }
		case 3: {temp.setTexture(TextureMap["wQ"]); break; }
		}
	}
	else if (color == PieceColor::Black) {
		switch (n) {
		case 0: {temp.setTexture(TextureMap["bR"]); break; }
		case 1: {temp.setTexture(TextureMap["bKn"]); break; }
		case 2: {temp.setTexture(TextureMap["bB"]); break; }
		case 3: {temp.setTexture(TextureMap["bQ"]); break; }
		}
	}
	temp.setPosition(833+84*n, 318);
	return temp;
}

void Chessboard::RenderPromotion(PieceColor color){

	promotion = true;

	rook = PromotionSpriteHandler(color, 0);
	knight = PromotionSpriteHandler(color, 1);
	bishop = PromotionSpriteHandler(color, 2);
	queen = PromotionSpriteHandler(color, 3);

}

void Chessboard::Initialize() {
	//initialize board status	
	promotion = false;
	for (int i = 0; i < 8; i++) {
		
		for (int j = 0; j < 8; j++) {

			//Heavy Pieces
			if (j == 0 || j == 7) {
				//rooks
				if (i == 0 || i == 7) { setPiece(j==0 ? PieceColor::Black : PieceColor::White,
					PieceID::Rook, { i, j }); }
				//knights
				if (i == 1 || i == 6) { setPiece(j == 0 ? PieceColor::Black : PieceColor::White,
					PieceID::Knight, { i, j }); }
				//bishops
				if (i == 2 || i == 5) { setPiece(j == 0 ? PieceColor::Black : PieceColor::White,
					PieceID::Bishop, { i, j }); }
				//queen
				if (i == 3) { setPiece(j == 0 ? PieceColor::Black : PieceColor::White,
					PieceID::Queen, { i, j }); }
				//king
				if (i == 4) { setPiece(j == 0 ? PieceColor::Black : PieceColor::White,
					PieceID::King, { i, j });
				j == 0 ? BlackKingCoordinates = { i, j } : WhiteKingCoordinates = { i, j };
				}
			}
			
			//Pawns
			if (j == 1 || j == 6) {
				setPiece(j == 1 ? PieceColor::Black : PieceColor::White,
					PieceID::Pawn, { i, j });
			}

			//Empty Fields
			if (j > 1 && j < 6) {
				Board[i][j].status = BoardStatus::Empty;
				Board[i][j].piece = nullptr;
			}


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
		if (promotion == true) {
			l_window.draw(rook);
			l_window.draw(knight);
			l_window.draw(bishop);
			l_window.draw(queen);
		}
	}

}

void Chessboard::ChangeStatusForHighlighted(int x, int y) {

	//if next field is empty
	if (Board[x][y].status == BoardStatus::Empty) {
		Board[x][y].status = BoardStatus::Highlighted;
		Board[x][y].StatRect = StatusSpriteHandler(
			Board[x][y].status, { x , y });
	}

}

void Chessboard::ChangeStatusForCapture(int x, int y) {

	Board[x][y].status = BoardStatus::Capture;
	Board[x][y].StatRect = StatusSpriteHandler(
		Board[x][y].status, { x, y });
}

void Chessboard::ChangeStatusToOccupied(int x, int y) {
	Board[x][y].status = BoardStatus::Occupied;
	Board[x][y].StatRect = StatusSpriteHandler(
		Board[x][y].status, { x, y });
}

void Chessboard::ChangeStatusToEmpty(int x, int y) {
	if (Board[x][y].status == BoardStatus::Highlighted) {
		Board[x][y].status = BoardStatus::Empty;
		Board[x][y].StatRect = StatusSpriteHandler(
			Board[x][y].status, { x, y });
	}
}

//Pawn show and hide----------------------------------------------------------
void Chessboard::ShowPawnPossibleMoves(sf::Vector2i ActiveCoord) {



	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {
		//white-----------------------------------------------------------------------------------
		if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {

			//two step move----------------------------------------------------------
			if (Board[ActiveCoord.x][ActiveCoord.y - 1].status == BoardStatus::Empty) {

				//for move one in two step move
				Board[ActiveCoord.x][ActiveCoord.y - 1].status = BoardStatus::Highlighted;
				Board[ActiveCoord.x][ActiveCoord.y - 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 1].status,
						{ ActiveCoord.x,  ActiveCoord.y - 1 });

				ChangeStatusForHighlighted(ActiveCoord.x, ActiveCoord.y - 2);
			}
		}

		else {
			//for one step move----------------------------------------------------------
			if (ActiveCoord.y - 1 >= 0) {
				ChangeStatusForHighlighted(ActiveCoord.x, ActiveCoord.y - 1);
			}
		}

		//capture for white ---------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x - 1][ActiveCoord.y - 1].piece->getPieceColor() == PieceColor::Black) {
				ChangeStatusForCapture(ActiveCoord.x - 1, ActiveCoord.y - 1);
			}
		}
		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x + 1][ActiveCoord.y - 1].piece->getPieceColor() == PieceColor::Black) {
				ChangeStatusForCapture(ActiveCoord.x + 1, ActiveCoord.y - 1);
			}
		}

		//En passant
		if (ActiveCoord.y == 3) {

			//right
			if ((ActiveCoord.x + 1) < 8) {

				
				if (Board[ActiveCoord.x + 1][ActiveCoord.y].status == BoardStatus::Occupied &&
					Board[ActiveCoord.x + 1][ActiveCoord.y].piece->getPieceColor() == PieceColor::Black &&
					Board[ActiveCoord.x + 1][ActiveCoord.y].piece->getPieceID() == PieceID::Pawn) {
					sf::Vector2i temp{ ActiveCoord.x + 1, ActiveCoord.y - 2 };
					if (PreviousCoordinates == temp) {
						Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status = BoardStatus::Capture;
						Board[ActiveCoord.x + 1][ActiveCoord.y - 1].StatRect = StatusSpriteHandler(
							Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status, { ActiveCoord.x + 1, ActiveCoord.y - 1 });
					}
				}


			}

			//left
			if ((ActiveCoord.x - 1) >= 0) {
				if (Board[ActiveCoord.x - 1][ActiveCoord.y].status == BoardStatus::Occupied &&
					Board[ActiveCoord.x - 1][ActiveCoord.y].piece->getPieceColor() == PieceColor::Black &&
					Board[ActiveCoord.x - 1][ActiveCoord.y].piece->getPieceID() == PieceID::Pawn) {
					sf::Vector2i temp{ ActiveCoord.x - 1, ActiveCoord.y - 2 };
					if (PreviousCoordinates == temp) {
						Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status = BoardStatus::Capture;
						Board[ActiveCoord.x - 1][ActiveCoord.y - 1].StatRect = StatusSpriteHandler(
							Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status, { ActiveCoord.x - 1, ActiveCoord.y - 1 });
					}
				}
}
		}
	}
	
	//black--------------------------------------------------------------------------------------

	else {
		if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {
			//two step move------------------------------------------------------------------------

			if (Board[ActiveCoord.x][ActiveCoord.y + 1].status == BoardStatus::Empty) {

				//for move one in two step move
				Board[ActiveCoord.x][ActiveCoord.y + 1].status = BoardStatus::Highlighted;
				Board[ActiveCoord.x][ActiveCoord.y + 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 1].status,
						{ ActiveCoord.x,  ActiveCoord.y + 1 });

				//for move two in two step move
				ChangeStatusForHighlighted(ActiveCoord.x, ActiveCoord.y + 2);
			}

		} else {
			//for one step move------------------------------------------------------------------
			if (ActiveCoord.y + 1 < 8) {
				ChangeStatusForHighlighted(ActiveCoord.x, ActiveCoord.y + 1);
			}
		}
		//capture for black----------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y + 1) < 8) {
			if (Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x - 1][ActiveCoord.y + 1].piece->getPieceColor() == PieceColor::White) {
				ChangeStatusForCapture(ActiveCoord.x - 1, ActiveCoord.y + 1);
			}
		}

		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y + 1) < 8) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x + 1][ActiveCoord.y + 1].piece->getPieceColor() == PieceColor::White) {
				ChangeStatusForCapture(ActiveCoord.x + 1, ActiveCoord.y + 1);
			}
		}

		//En passant
		if (ActiveCoord.y == 4) {

			//right
			if ((ActiveCoord.x + 1) < 8) {


				if (Board[ActiveCoord.x + 1][ActiveCoord.y].status == BoardStatus::Occupied &&
					Board[ActiveCoord.x + 1][ActiveCoord.y].piece->getPieceColor() == PieceColor::White &&
					Board[ActiveCoord.x + 1][ActiveCoord.y].piece->getPieceID() == PieceID::Pawn) {
					sf::Vector2i temp{ ActiveCoord.x + 1, ActiveCoord.y + 2 };
					if (PreviousCoordinates == temp) {
						Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status = BoardStatus::Capture;
						Board[ActiveCoord.x + 1][ActiveCoord.y + 1].StatRect = StatusSpriteHandler(
							Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status, { ActiveCoord.x + 1, ActiveCoord.y + 1 });
					}
				}


			}

			//left
			if ((ActiveCoord.x - 1) >= 0) {
				if (Board[ActiveCoord.x - 1][ActiveCoord.y].status == BoardStatus::Occupied &&
					Board[ActiveCoord.x - 1][ActiveCoord.y].piece->getPieceColor() == PieceColor::White &&
					Board[ActiveCoord.x - 1][ActiveCoord.y].piece->getPieceID() == PieceID::Pawn) {
					sf::Vector2i temp{ ActiveCoord.x - 1, ActiveCoord.y + 2 };
					if (PreviousCoordinates == temp) {
						Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status = BoardStatus::Capture;
						Board[ActiveCoord.x - 1][ActiveCoord.y + 1].StatRect = StatusSpriteHandler(
							Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status, { ActiveCoord.x - 1, ActiveCoord.y + 1 });
					}
				}
			}

		}
	}	
}

void Chessboard::HidePawnPossibleMoves(sf::Vector2i ActiveCoord) {
	
	//white-----------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {
		if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {

			//two step move-----------------------------------------------------------------------
			if (Board[ActiveCoord.x][ActiveCoord.y - 1].status == BoardStatus::Highlighted) {

				//for move one in two step move
				Board[ActiveCoord.x][ActiveCoord.y - 1].status = BoardStatus::Empty;
				Board[ActiveCoord.x][ActiveCoord.y - 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 1].status,
						{ ActiveCoord.x,  ActiveCoord.y - 1 });

				ChangeStatusToEmpty(ActiveCoord.x, ActiveCoord.y - 2);
			}			
		}

		else {
			//for one step move---------------------------------------------------------------
			if (ActiveCoord.y - 1 >= 0) {
				ChangeStatusToEmpty(ActiveCoord.x, ActiveCoord.y - 1);
			}
		}

		//capture and en passant for white ---------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status == BoardStatus::Capture) {

				if (Board[ActiveCoord.x - 1][ActiveCoord.y - 1].piece == nullptr) {
					Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status = BoardStatus::Empty;
					Board[ActiveCoord.x - 1][ActiveCoord.y - 1].StatRect = StatusSpriteHandler(
						Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status, { ActiveCoord.x - 1, ActiveCoord.y - 1 });
				}
				else 
				ChangeStatusToOccupied(ActiveCoord.x - 1, ActiveCoord.y - 1);
			}
		}
		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status == BoardStatus::Capture) {

				if (Board[ActiveCoord.x + 1][ActiveCoord.y - 1].piece == nullptr) {
					Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status = BoardStatus::Empty;
					Board[ActiveCoord.x + 1][ActiveCoord.y - 1].StatRect = StatusSpriteHandler(
						Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status, { ActiveCoord.x + 1, ActiveCoord.y - 1 });
				}
				else

				ChangeStatusToOccupied(ActiveCoord.x + 1, ActiveCoord.y - 1);
			}
		}



	}
	
	//black-----------------------------------------------------------------------------
	else { 
		
		//two step move---------------------------------------------------------------
		if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {
			

			if (Board[ActiveCoord.x][ActiveCoord.y + 1].status == BoardStatus::Highlighted) {

				//for move one in two step move
				Board[ActiveCoord.x][ActiveCoord.y + 1].status = BoardStatus::Empty;
				Board[ActiveCoord.x][ActiveCoord.y + 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 1].status,
						{ ActiveCoord.x,  ActiveCoord.y + 1 });

				//for move two in two step move
				ChangeStatusToEmpty(ActiveCoord.x, ActiveCoord.y + 2);
			}

		}

		//for one step move-------------------------------------------------------------------
		else {
			
			if (ActiveCoord.y + 1 < 8) {
				ChangeStatusToEmpty(ActiveCoord.x, ActiveCoord.y + 1);
			}
		}

		//capture and en passant for black----------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y + 1) < 8) {

			if (Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status == BoardStatus::Capture) {

				if (Board[ActiveCoord.x - 1][ActiveCoord.y + 1].piece == nullptr) {
					Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status = BoardStatus::Empty;
					Board[ActiveCoord.x - 1][ActiveCoord.y + 1].StatRect = StatusSpriteHandler(
						Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status, { ActiveCoord.x - 1, ActiveCoord.y + 1 });
				}
				else

				ChangeStatusToOccupied(ActiveCoord.x - 1, ActiveCoord.y + 1);
			}
		}
		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y + 1) < 8) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status == BoardStatus::Capture) {

				if (Board[ActiveCoord.x + 1][ActiveCoord.y + 1].piece == nullptr) {
					Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status = BoardStatus::Empty;
					Board[ActiveCoord.x + 1][ActiveCoord.y + 1].StatRect = StatusSpriteHandler(
						Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status, { ActiveCoord.x - 1, ActiveCoord.y - 1 });
				}
				else

				ChangeStatusToOccupied(ActiveCoord.x + 1, ActiveCoord.y + 1);
			}
		}
	}
}


//Rook show and hide----------------------------------------------------------
void Chessboard::ShowRookPossibleMoves(sf::Vector2i ActiveCoord) {

	//skoro te while tak dobrze dzialaja w bishop to ma sens je tu tez zastosowac
	//pa pa wymuszone ify

	//White---------------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7) {
				//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 1, y);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y);
			x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
				//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 1, y);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y);
			x++;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x, y - 1);
					break;
				}
			}
			ChangeStatusForHighlighted(x, y - 1);
			y--;

		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x, y + 1);
					break;
				}
			}
			ChangeStatusForHighlighted(x, y + 1);
			y++;
		}
	}

	


	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y].status == BoardStatus::Occupied) {
					if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) {
						ChangeStatusForCapture(x - 1, y);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x - 1, y);
				x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y].status == BoardStatus::Occupied) {
					if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) {
						ChangeStatusForCapture(x + 1, y);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x + 1, y);
				x++;
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x][y - 1].status == BoardStatus::Occupied) {
					if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) {
						ChangeStatusForCapture(x, y - 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x, y - 1);
				y--;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {
			

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x, y + 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x , y + 1);
			y++;
		}
	}

}

void Chessboard::HideRookPossibleMoves(sf::Vector2i ActiveCoord) {

	//tu w sumie tez moglbym pozmieniac te ify i dodac je do while'ow
	//ale to pozniej, na razie poki dziala niech zostanie

	//chociaz jednak zmienie aby mozna bylo skopiowac do queen

	//White---------------------------------------------------------------------------------
	//if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x - 1][y].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x - 1, y);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x - 1, y);
			x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {

			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x + 1][y].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x + 1, y);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x + 1, y);
			x++;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {

			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x][y - 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x, y - 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x, y - 1);
			y--;
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x][y + 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x, y + 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x, y + 1);
			y++;
		}
	//}
}


//Knight show and hide--------------------------------------------------------
void Chessboard::ShowKnightPossibleMoves(sf::Vector2i ActiveCoord){

	//White---------------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;



		//top - left----------------------
		if ((x - 1 >= 0 && y - 2 >= 0)) {

			//if next field is occupied
			if (Board[x - 1][y - 2].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 2].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 1, y - 2);
				}
			}
			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y - 2);
		}

		//top - right----------------------
		if ((x + 1 <= 7 && y - 2 >=  0)) {

			//if next field is occupied
			if (Board[x + 1][y - 2].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 2].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 1, y - 2);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y - 2);
		}

		//bottom - left----------------------
		if ((x - 1 >= 0 && y + 2 <= 7)) {

			//if next field is occupied
			if (Board[x - 1][y + 2].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 2].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 1, y + 2);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y + 2);

		}

		//bottom - right----------------------
		if ((x + 1 <= 7 && y + 2 <= 7)) {

			//if next field is occupied
			if (Board[x + 1][y + 2].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 2].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 1, y + 2);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y + 2);
		}



		//left - bottom----------------------
		if ((x - 2 >= 0 && y + 1 <= 7)) {

			//if next field is occupied
			if (Board[x - 2][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 2][y + 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 2, y + 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 2, y + 1);
		}

		//left - top----------------------
		if ((x - 2 >= 0 && y - 1 >= 0)) {

			//if next field is occupied
			if (Board[x - 2][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 2][y - 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 2, y - 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 2, y - 1);
		}

		//right - top------------------
		if ((x + 2 <= 7 && y + 1 <= 7)) {

			//if next field is occupied
			if (Board[x + 2][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 2][y + 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 2, y + 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 2, y + 1);

		}

		//right - bottom------------------
		if ((x + 2 <= 7 && y - 1 >= 0)) {

			//if next field is occupied
			if (Board[x + 2][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 2][y - 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 2, y - 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 2, y - 1);

		}
	} 

	

	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;



		//top - left----------------------
		if ((x - 1 >= 0 && y - 2 >= 0)) {

			//if next field is occupied
			if (Board[x - 1][y - 2].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 2].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x - 1, y - 2);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y - 2);
		}

		//top - right----------------------
		if ((x + 1 <= 7 && y - 2 >= 0)) {

			//if next field is occupied
			if (Board[x + 1][y - 2].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 2].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x + 1, y - 2);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y - 2);
		}

		//bottom - left----------------------
		if ((x - 1 >= 0 && y + 2 <= 7)) {

			//if next field is occupied
			if (Board[x - 1][y + 2].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 2].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x - 1, y + 2);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y + 2);

		}

		//bottom - right----------------------
		if ((x + 1 <= 7 && y + 2 <= 7)) {

			//if next field is occupied
			if (Board[x + 1][y + 2].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 2].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x + 1, y + 2);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y + 2);
		}



		//left - bottom----------------------
		if ((x - 2 >= 0 && y + 1 <= 7)) {

			//if next field is occupied
			if (Board[x - 2][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 2][y + 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x - 2, y + 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 2, y + 1);
		}

		//left - top----------------------
		if ((x - 2 >= 0 && y - 1 >= 0)) {

			//if next field is occupied
			if (Board[x - 2][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 2][y - 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x - 2, y - 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 2, y - 1);
		}

		//right - bottom------------------
		if ((x + 2 <= 7 && y + 1 <= 7)) {

			//if next field is occupied
			if (Board[x + 2][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 2][y + 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x + 2, y + 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 2, y + 1);
		}

		//right - top------------------
		if ((x + 2 <= 7 && y - 1 >= 0)) {

			//if next field is occupied
			if (Board[x + 2][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 2][y - 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x + 2, y - 1);
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 2, y - 1);

		}
	}
}

void Chessboard::HideKnightPossibleMoves(sf::Vector2i ActiveCoord){
	//White---------------------------------------------------------------------------------
	//if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;



		//top - left----------------------
		if ((x - 1 >= 0 && y - 2 >= 0)) {

			//if next field is occupied
			//if (Board[x - 1][y - 2].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 2].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x - 1, y - 2);
				}
			//}

			//if next field is empty
				ChangeStatusToEmpty(x - 1, y - 2);

		}

		//top - right----------------------
		if ((x + 1 <= 7 && y - 2 >= 0)) {

			//if next field is occupied
				if (Board[x + 1][y - 2].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x + 1, y - 2);
				}

			//if next field is empty
				ChangeStatusToEmpty(x + 1, y - 2);
		}

		//bottom - left----------------------
		if ((x - 1 >= 0 && y + 2 <= 7)) {

			//if next field is occupied
				if (Board[x - 1][y + 2].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x - 1, y + 2);
				}

			//if next field is empty
				ChangeStatusToEmpty(x - 1, y + 2);

		}

		//bottom - right----------------------
		if ((x + 1 <= 7 && y + 2 <= 7)) {

			//if next field is occupied
				if (Board[x + 1][y + 2].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x + 1, y + 2);
				}

			//if next field is empty
				ChangeStatusToEmpty(x + 1, y + 2);
		}



		//left - bottom----------------------
		if ((x - 2 >= 0 && y + 1 <= 7)) {

			//if next field is occupied
				if (Board[x - 2][y + 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x - 2, y + 1);
				}

			//if next field is empty
				ChangeStatusToEmpty(x - 2, y + 1);

		}

		//left - top----------------------
		if ((x - 2 >= 0 && y - 1 >= 0)) {

			//if next field is occupied
			//if (Board[x - 2][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 2][y - 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x - 2, y - 1);
				}
			//}

			//if next field is empty
				ChangeStatusToEmpty(x - 2, y - 1);

		}

		//right - bottom------------------
		if ((x + 2 <= 7 && y + 1 <= 7)) {

			//if next field is occupied
			//if (Board[x + 2][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 2][y + 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x + 2, y + 1);
				}
			//}

			//if next field is empty
				ChangeStatusToEmpty(x + 2, y + 1);

		}

		//right - bottom------------------
		if ((x + 2 <= 7 && y - 1 >= 0)) {

			//if next field is occupied
				if (Board[x + 2][y - 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x + 2, y - 1);
				}

			//if next field is empty
				ChangeStatusToEmpty(x + 2, y - 1);

		}
	//}
}


//Bishop show and hide--------------------------------------------------------
void Chessboard::ShowBishopPossibleMoves(sf::Vector2i ActiveCoord) {

	//dlaczego te while sa tu takie jak sa?
	//to jest bardzo dobre pytanie
	//na ktore odpowiedziec nie potrafie

	//o, te nowe warunki od razu maja wiecej sensu
	//przynajmniej juz mnie nie dziwi ze dzialaja
	//i jezeli przy nich wywali to juz nie wiem jak to zrobic abym rozumial i dzialo

	//White--------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;

		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
						ChangeStatusForCapture(x - 1, y - 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x - 1, y - 1);
				x--; y--;
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
						ChangeStatusForCapture(x + 1, y - 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x + 1, y - 1);
				x++; y--;
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
						ChangeStatusForCapture(x - 1, y + 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x - 1, y + 1);
				x--; y++;
			//}
		}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
						ChangeStatusForCapture(x + 1, y + 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x + 1, y + 1);
				x++; y++;
			//}
		}

	}
	
	//Black--------------------------------------------------------------------------
else {

		

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) {
						ChangeStatusForCapture(x - 1, y - 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x - 1, y - 1);
				x--; y--;
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) {
						ChangeStatusForCapture(x + 1, y - 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x + 1, y - 1);
				x++; y--;
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) {
						ChangeStatusForCapture(x - 1, y + 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x - 1, y + 1);
				x--; y++;
			}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) {
						ChangeStatusForCapture(x + 1, y + 1);
						break;
					}
				}

				//if next field is empty
				ChangeStatusForHighlighted(x + 1, y + 1);
				x++; y++;
		}
	}
}

void Chessboard::HideBishopPossibleMoves(sf::Vector2i ActiveCoord) {

	//White----------------------------------------------------------------
	//if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;}
			else if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x - 1, y - 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x - 1, y - 1);
			x--; y--;
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x + 1][y - 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x + 1, y - 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x + 1, y - 1);
			x++; y--;
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;


		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied

			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
			}

			else if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x - 1, y + 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x - 1, y + 1);
			x--; y++;
		}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x + 1][y + 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x + 1, y + 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x + 1, y + 1);
			x++; y++;
		}

	//}

}


//Queen show and hide---------------------------------------------------------
void Chessboard::ShowQueenPossibleMoves(sf::Vector2i ActiveCoord){
	//White---------------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 1, y);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y);
			x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 1, y);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y);
			x++;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x, y - 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x, y - 1);
			y--;
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x, y + 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x, y + 1);
			y++;
		}

		x = ActiveCoord.x;
		y = ActiveCoord.y;
		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 1, y - 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y - 1);
			x--; y--;
			//}
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 1, y - 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y - 1);
			x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x - 1, y + 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y + 1);
			x--; y++;
		}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					ChangeStatusForCapture(x + 1, y + 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y + 1);
			x++; y++;
		}
	}




	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x - 1, y);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y);
			x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x + 1, y);
					break;
				}

			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y);
			x++;
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x, y - 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x, y - 1);
			y--;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x, y + 1);
					break;
				}
			}
			//if next field is empty
			ChangeStatusForHighlighted(x, y + 1);

			y++;
		}

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x - 1, y - 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y - 1);
			x--; y--;
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x + 1, y - 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y - 1);
			x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x - 1, y + 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x - 1, y + 1);
			x--; y++;
		}
		//}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					ChangeStatusForCapture(x + 1, y + 1);
					break;
				}
			}

			//if next field is empty
			ChangeStatusForHighlighted(x + 1, y + 1);
			x++; y++;
		}
	}
}

void Chessboard::HideQueenPossibleMoves(sf::Vector2i ActiveCoord) {

	//White---------------------------------------------------------------
	//if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x - 1][y].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x - 1, y);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x - 1, y);
			x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {

			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x + 1][y].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x + 1, y);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x + 1, y);
			x++;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {

			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x][y - 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x, y - 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x, y - 1);
			y--;
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x][y + 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x, y + 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x, y + 1);
			y++;
		}

		x = ActiveCoord.x;
		y = ActiveCoord.y;
		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x - 1, y - 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x - 1, y - 1);
			x--; y--;
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x + 1][y - 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x + 1, y - 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x + 1, y - 1);
			x++; y--;
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;


		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied

			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
			}

			else if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x - 1, y + 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x - 1, y + 1);
			x--; y++;
		}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x + 1][y + 1].status == BoardStatus::Capture) {
				ChangeStatusToOccupied(x + 1, y + 1);
				break;
			}

			//if next field is empty
			ChangeStatusToEmpty(x + 1, y + 1);
			x++; y++;
		}

	//}
}


//King show and hide----------------------------------------------------------
void Chessboard::ShowKingPossibleMoves(sf::Vector2i ActiveCoord){

	//White---------------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;

		//Castle
		if (Board[x][y].piece->getMoveCount() == 0) {
			if (Board[x + 3][y].status == BoardStatus::Occupied && 
				Board[x + 3][y].piece->getMoveCount() == 0)
				ShowShortCastle(PieceColor::White);

			if (Board[x - 4][y].status == BoardStatus::Occupied &&
				Board[x - 4][y].piece->getMoveCount() == 0)
				ShowLongCastle(PieceColor::White);
		}



		//left---------------
		if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({x - 1, y}, PieceColor::White))
					ChangeStatusForCapture(x - 1, y);
				} 
			} else if (!CheckIfFieldIsAttacked({ x - 1, y }, PieceColor::White))
			ChangeStatusForHighlighted(x - 1, y);

			//if next field is empty
			
		}

		//right
		if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({ x + 1, y }, PieceColor::White))
					ChangeStatusForCapture(x + 1, y);
				} 
			} else if (!CheckIfFieldIsAttacked({ x + 1, y }, PieceColor::White))
			ChangeStatusForHighlighted(x + 1, y);

			//if next field is empty
			
		}

		//up
		if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({ x, y - 1 }, PieceColor::White))
					ChangeStatusForCapture(x, y - 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x, y - 1 }, PieceColor::White))
			ChangeStatusForHighlighted(x, y - 1);

			//if next field is empty
			
		}

		//down
		if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({ x, y + 1 }, PieceColor::White))
					ChangeStatusForCapture(x, y + 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x, y + 1 }, PieceColor::White))
			ChangeStatusForHighlighted(x, y + 1);

			//if next field is empty
			
		}

		//top-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({ x - 1, y - 1 }, PieceColor::White))
					ChangeStatusForCapture(x - 1, y - 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x - 1, y - 1 }, PieceColor::White))
			ChangeStatusForHighlighted(x - 1, y - 1);

			//if next field is empty
			
		}

		//top-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({ x + 1, y - 1 }, PieceColor::White))
					ChangeStatusForCapture(x + 1, y - 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x + 1, y - 1 }, PieceColor::White))
			ChangeStatusForHighlighted(x + 1, y - 1);

			//if next field is empty
			
		}

		//bottom-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({ x - 1, y + 1 }, PieceColor::White))
					ChangeStatusForCapture(x - 1, y + 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x - 1, y + 1 }, PieceColor::White))
			ChangeStatusForHighlighted(x - 1, y + 1);

			//if next field is empty
			
		}

		//bottom-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					if (!CheckIfFieldIsAttacked({ x + 1, y + 1 }, PieceColor::White))
					ChangeStatusForCapture(x + 1, y + 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x + 1, y + 1 }, PieceColor::White))
			ChangeStatusForHighlighted(x + 1, y + 1);

			//if next field is empty
			
		}
	}


	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		
		//Short Castle
		if (Board[x][y].piece->getMoveCount() == 0) {
			if (Board[x + 3][y].status == BoardStatus::Occupied &&
				Board[x + 3][y].piece->getMoveCount() == 0)
				ShowShortCastle(PieceColor::Black);

			if (Board[x - 4][y].status == BoardStatus::Occupied &&
				Board[x - 4][y].piece->getMoveCount() == 0)
				ShowLongCastle(PieceColor::Black);
		}


		//left---------------
		if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) {
					if (!CheckIfFieldIsAttacked({ x - 1, y}, PieceColor::Black))
					ChangeStatusForCapture(x - 1, y);
				}
			} else if (!CheckIfFieldIsAttacked({ x - 1, y }, PieceColor::Black))
			ChangeStatusForHighlighted(x - 1, y);

			//if next field is empty
			
		}

		//right
		if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) {
					if (!CheckIfFieldIsAttacked({ x + 1, y }, PieceColor::Black))
					ChangeStatusForCapture(x + 1, y);
				}
			} else if (!CheckIfFieldIsAttacked({ x + 1, y }, PieceColor::Black))
			ChangeStatusForHighlighted(x + 1, y);

			//if next field is empty
			
		}
		
		//down
		if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied &&
				Board[x][y + 1].piece->getPieceColor() == PieceColor::White) {
				if (!CheckIfFieldIsAttacked({ x, y + 1 }, PieceColor::Black))
					ChangeStatusForCapture(x, y + 1);
				} else if (!CheckIfFieldIsAttacked({ x, y + 1 }, PieceColor::Black))
			ChangeStatusForHighlighted(x, y + 1);
			

			//if next field is empty
			
		}

		//up
		if (y - 1 >= 0 && y - 1 <= 7) {
			

			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) {
					if (!CheckIfFieldIsAttacked({ x, y - 1 }, PieceColor::Black))
					ChangeStatusForCapture(x, y - 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x, y - 1 }, PieceColor::Black))
			ChangeStatusForHighlighted(x, y - 1);
			//if next field is empty
			


		}

		//top-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) {
					if (!CheckIfFieldIsAttacked({ x - 1, y - 1 }, PieceColor::Black))
					ChangeStatusForCapture(x - 1, y - 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x - 1, y - 1 }, PieceColor::Black))
			ChangeStatusForHighlighted(x - 1, y - 1);

			//if next field is empty
			
		}

		//top-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				 if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) {
					 if (!CheckIfFieldIsAttacked({ x + 1, y - 1 }, PieceColor::Black))
					 ChangeStatusForCapture(x + 1, y - 1);

				 }
			} else if (!CheckIfFieldIsAttacked({ x + 1, y - 1 }, PieceColor::Black))
			ChangeStatusForHighlighted(x + 1, y - 1);

			//if next field is empty
			
		}

		//bottom-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					if (!CheckIfFieldIsAttacked({ x - 1, y + 1 }, PieceColor::Black))
					ChangeStatusForCapture(x - 1, y + 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x - 1, y + 1 }, PieceColor::Black))
			ChangeStatusForHighlighted(x - 1, y + 1);

			//if next field is empty
			
		}

		//bottom-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					if (!CheckIfFieldIsAttacked({ x + 1, y + 1 }, PieceColor::Black))
					ChangeStatusForCapture(x + 1, y + 1);
				}
			} else if (!CheckIfFieldIsAttacked({ x + 1, y + 1 }, PieceColor::Black))
			ChangeStatusForHighlighted(x + 1, y + 1);

			//if next field is empty
			
		}
	}
}

void Chessboard::HideKingPossibleMoves(sf::Vector2i ActiveCoord){
	//White---------------------------------------------------------------------------------
	//if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;

		if (x == 4 && (y == 0 || y == 7)) {
			//Short castle hide
			if (Board[x + 3][y].piece != nullptr && Board[x + 3][y].piece->getPieceID() == PieceID::Rook) {
				if (Board[x + 3][y].status == BoardStatus::Highlighted) {

					Board[x + 3][y].status = BoardStatus::Occupied;
					Board[x + 3][y].StatRect = StatusSpriteHandler(
						Board[x + 3][y].status, { x + 3, y });
				}
			}

			//Short castle hide
			if (Board[x - 4][y].piece != nullptr && Board[x - 4][y].piece->getPieceID() == PieceID::Rook) {
				if (Board[x - 4][y].status == BoardStatus::Highlighted) {

					Board[x - 4][y].status = BoardStatus::Occupied;
					Board[x - 4][y].StatRect = StatusSpriteHandler(
						Board[x - 4][y].status, { x - 4, y });
				}
			}

		}
			
		

		//left---------------
		if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
				if (Board[x - 1][y].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x - 1, y);
				}

			//if next field is empty
				ChangeStatusToEmpty(x - 1, y);
		}

		//right
		if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
				if (Board[x + 1][y].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x + 1, y);
				}

			//if next field is empty
				ChangeStatusToEmpty(x + 1, y);
		}

		//up
		if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
				if (Board[x][y - 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x, y - 1);
				}

			//if next field is empty
				ChangeStatusToEmpty(x, y - 1);
		}

		//down
		if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
				if (Board[x][y + 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x, y + 1);
				}

			//if next field is empty
				ChangeStatusToEmpty(x, y + 1);
		}

		//top-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
				if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x - 1, y - 1);
				}

			//if next field is empty
				ChangeStatusToEmpty(x - 1, y - 1);
		}

		//top-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
				if (Board[x + 1][y - 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x + 1, y - 1);
				}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Highlighted) {
				ChangeStatusToEmpty(x + 1, y - 1);
			}
		}

		//bottom-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
				if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x - 1, y + 1);
				}

			//if next field is empty
				ChangeStatusToEmpty(x - 1, y + 1);
		}

		//bottom-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
				if (Board[x + 1][y + 1].status == BoardStatus::Capture) {
					ChangeStatusToOccupied(x + 1, y + 1);
				}

			//if next field is empty
				ChangeStatusToEmpty(x + 1, y + 1);
		}
	//}
}
