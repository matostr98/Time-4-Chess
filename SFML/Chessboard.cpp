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

void Chessboard::setPiece(PieceColor color, PieceID id, sf::Vector2i coord){
	ChessPiece p(color, id, coord);
	Board[coord.x][coord.y].piece = std::make_shared<ChessPiece>(p);
	Board[coord.x][coord.y].status = BoardStatus::Occupied;

	Board[coord.x][coord.y].rect = PieceSpriteHandler(Board[coord.x][coord.y].piece->getPieceID(),
		Board[coord.x][coord.y].piece->getPieceColor(), coord);
}

Chessboard::Chessboard() {
	Sprites();
	Initialize();
}
Chessboard::~Chessboard() {}

void Chessboard::Move(sf::Vector2i ActiveCoord, sf::Vector2i NewCoord){
	//HidePossibleMoves(NewCoord);
	//new field
	Board[NewCoord.x][NewCoord.y].piece = Board[ActiveCoord.x][ActiveCoord.y].piece;
	Board[NewCoord.x][NewCoord.y].piece->increamentMoveCount(); //tu bylo active

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
	
	//opponent field (new field)
	Board[NewCoord.x][NewCoord.y].piece = nullptr;
	Board[NewCoord.x][NewCoord.y].piece = Board[ActiveCoord.x][ActiveCoord.y].piece;
	Board[NewCoord.x][NewCoord.y].piece->increamentMoveCount();

	Board[NewCoord.x][NewCoord.y].status = BoardStatus::Occupied;
	Board[NewCoord.x][NewCoord.y].rect =
		PieceSpriteHandler(Board[NewCoord.x][NewCoord.y].piece->getPieceID(),
			Board[NewCoord.x][NewCoord.y].piece->getPieceColor(), NewCoord);
	Board[NewCoord.x][NewCoord.y].StatRect =
		StatusSpriteHandler(Board[NewCoord.x][NewCoord.y].status, NewCoord);
	
	//to add - move sprite to the right!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//old field
	Board[ActiveCoord.x][ActiveCoord.y].piece = nullptr;
	Board[ActiveCoord.x][ActiveCoord.y].status = BoardStatus::Empty;
	Board[ActiveCoord.x][ActiveCoord.y].rect =
		StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);
	Board[ActiveCoord.x][ActiveCoord.y].StatRect =
		StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y].status, ActiveCoord);
	

}

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

BoardStatus Chessboard::getBoardStatus(sf::Vector2i coor) {
	return Board[coor.x][coor.y].status;
}

PieceColor Chessboard::getPieceColor(sf::Vector2i coor)
{
	return Board[coor.x][coor.y].piece->getPieceColor();	
}

void Chessboard::MakeActiveSprite(sf::Vector2i coord) {

	Board[coord.x][coord.y].status = BoardStatus::Active;
	Board[coord.x][coord.y].StatRect = StatusSpriteHandler(Board[coord.x][coord.y].status, coord);
	ShowPossibleMoves(coord);
}

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

void Chessboard::Initialize() {
	//initialize board status	

	for (int i = 0; i < 8; i++) {
		int j = 0;

		//Black 

		//rooks
		if (i == 0 || i == 7) {setPiece(PieceColor::Black, PieceID::Rook, { i, j });}
		//knights
		if (i == 1 || i == 6) {setPiece(PieceColor::Black, PieceID::Knight, { i, j });}
		//bishops
		if (i == 2 || i == 5) {setPiece(PieceColor::Black, PieceID::Bishop, { i, j });}
		//queen
		if (i == 3) {setPiece(PieceColor::Black, PieceID::Queen, { i, j });}
		//king
		if (i == 4) {setPiece(PieceColor::Black, PieceID::King, { i, j });}
		//pawns
		j = 1; setPiece(PieceColor::Black, PieceID::Pawn, { i, j });
			

		//Empty slots
		for (j = 2; j < 6; j++) {
			Board[i][j].status = BoardStatus::Empty;
			Board[i][j].piece = nullptr;
		}

		//White

		//pawns
		j = 6;	
		setPiece(PieceColor::White, PieceID::Pawn, { i, j });
		
		j = 7;
		//rooks
		if (i == 0 || i == 7) {setPiece(PieceColor::White, PieceID::Rook, { i, j });}
		//knights
		if (i == 1 || i == 6) {setPiece(PieceColor::White, PieceID::Knight, { i, j });}
		//bishops
		if (i == 2 || i == 5) {setPiece(PieceColor::White, PieceID::Bishop, { i, j });}
		//queen
		if (i == 3) {setPiece(PieceColor::White, PieceID::Queen, { i, j });}
		//king
		if (i == 4) {setPiece(PieceColor::White, PieceID::King, { i, j });}

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

				if (Board[ActiveCoord.x][ActiveCoord.y - 2].status == BoardStatus::Empty) {

					//for move two in two step move
					Board[ActiveCoord.x][ActiveCoord.y - 2].status = BoardStatus::Highlighted;
					Board[ActiveCoord.x][ActiveCoord.y - 2].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 2].status,
							{ ActiveCoord.x,  ActiveCoord.y - 2 });
				}
			}					
		}

		else {
			//for one step move----------------------------------------------------------
			if (ActiveCoord.y - 1 >= 0) {
				if (Board[ActiveCoord.x][ActiveCoord.y - 1].status == BoardStatus::Empty) {
					Board[ActiveCoord.x][ActiveCoord.y - 1].status = BoardStatus::Highlighted;
					Board[ActiveCoord.x][ActiveCoord.y - 1].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 1].status,
							{ ActiveCoord.x,  ActiveCoord.y - 1 });
				}
			}
		}

		//capture for white ---------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x - 1][ActiveCoord.y - 1].piece->getPieceColor() == PieceColor::Black) {

				Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status = BoardStatus::Capture;
				Board[ActiveCoord.x - 1][ActiveCoord.y - 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status,
						{ ActiveCoord.x - 1,  ActiveCoord.y - 1 });
			}
		}
		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x + 1][ActiveCoord.y - 1].piece->getPieceColor() == PieceColor::Black) {

				Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status = BoardStatus::Capture;
				Board[ActiveCoord.x + 1][ActiveCoord.y - 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status,
						{ ActiveCoord.x + 1,  ActiveCoord.y - 1 });
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

				if (Board[ActiveCoord.x][ActiveCoord.y + 2].status == BoardStatus::Empty) {

					//for move two in two step move
					Board[ActiveCoord.x][ActiveCoord.y + 2].status = BoardStatus::Highlighted;
					Board[ActiveCoord.x][ActiveCoord.y + 2].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 2].status,
							{ ActiveCoord.x,  ActiveCoord.y + 2 });
				}
			}

		} else {
			//for one step move------------------------------------------------------------------
			if (ActiveCoord.y + 1 < 8) {
				if (Board[ActiveCoord.x][ActiveCoord.y + 1].status == BoardStatus::Empty) {
					Board[ActiveCoord.x][ActiveCoord.y + 1].status = BoardStatus::Highlighted;
					Board[ActiveCoord.x][ActiveCoord.y + 1].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 1].status,
							{ ActiveCoord.x,  ActiveCoord.y + 1 });
				}
			}
		}
		//capture for black----------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y + 1) < 8) {
			if (Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x - 1][ActiveCoord.y + 1].piece->getPieceColor() == PieceColor::White) {
				Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status = BoardStatus::Capture;
				Board[ActiveCoord.x - 1][ActiveCoord.y + 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status,
						{ ActiveCoord.x - 1,  ActiveCoord.y + 1 });
			}
		}
		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y + 1) < 8) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status == BoardStatus::Occupied
				&&Board[ActiveCoord.x + 1][ActiveCoord.y + 1].piece->getPieceColor() == PieceColor::White) {
				Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status = BoardStatus::Capture;
				Board[ActiveCoord.x + 1][ActiveCoord.y + 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status,
						{ ActiveCoord.x + 1,  ActiveCoord.y + 1 });
			}
		}
	}
}

void Chessboard::HidePawnPossibleMoves(sf::Vector2i ActiveCoord) {

	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {
		//white-----------------------------------------------------------------------------
		if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {

			//two step move-----------------------------------------------------------------------
			if (Board[ActiveCoord.x][ActiveCoord.y - 1].status == BoardStatus::Highlighted) {

				//for move one in two step move
				Board[ActiveCoord.x][ActiveCoord.y - 1].status = BoardStatus::Empty;
				Board[ActiveCoord.x][ActiveCoord.y - 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 1].status,
						{ ActiveCoord.x,  ActiveCoord.y - 1 });

				if (Board[ActiveCoord.x][ActiveCoord.y - 2].status == BoardStatus::Highlighted) {

					//for move two in two step move
					Board[ActiveCoord.x][ActiveCoord.y - 2].status = BoardStatus::Empty;
					Board[ActiveCoord.x][ActiveCoord.y - 2].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 2].status,
							{ ActiveCoord.x,  ActiveCoord.y - 2 });
				}
			}			
		}

		else {
			//for one step move---------------------------------------------------------------
			if (ActiveCoord.y - 1 >= 0) {
				if (Board[ActiveCoord.x][ActiveCoord.y - 1].status == BoardStatus::Highlighted) {
					Board[ActiveCoord.x][ActiveCoord.y - 1].status = BoardStatus::Empty;
					Board[ActiveCoord.x][ActiveCoord.y - 1].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y - 1].status,
							{ ActiveCoord.x,  ActiveCoord.y - 1 });
				}
			}
		}

		//capture for white ---------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status == BoardStatus::Capture
				&&Board[ActiveCoord.x - 1][ActiveCoord.y - 1].piece->getPieceColor() == PieceColor::Black) {

				Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status = BoardStatus::Occupied;
				Board[ActiveCoord.x - 1][ActiveCoord.y - 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x - 1][ActiveCoord.y - 1].status,
						{ ActiveCoord.x - 1,  ActiveCoord.y - 1 });
			}
		}
		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y - 1) >= 0) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status == BoardStatus::Capture
				&&Board[ActiveCoord.x + 1][ActiveCoord.y - 1].piece->getPieceColor() == PieceColor::Black) {

				Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status = BoardStatus::Occupied;
				Board[ActiveCoord.x + 1][ActiveCoord.y - 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x + 1][ActiveCoord.y - 1].status,
						{ ActiveCoord.x + 1,  ActiveCoord.y - 1 });
			}
		}

	}
	else { //black-----------------------------------------------------------------------------
		if (Board[ActiveCoord.x][ActiveCoord.y].piece->getMoveCount() == 0) {
			//two step move---------------------------------------------------------------

			if (Board[ActiveCoord.x][ActiveCoord.y + 1].status == BoardStatus::Highlighted) {

				//for move one in two step move
				Board[ActiveCoord.x][ActiveCoord.y + 1].status = BoardStatus::Empty;
				Board[ActiveCoord.x][ActiveCoord.y + 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 1].status,
						{ ActiveCoord.x,  ActiveCoord.y + 1 });

				if (Board[ActiveCoord.x][ActiveCoord.y + 2].status == BoardStatus::Highlighted) {

					//for move two in two step move
					Board[ActiveCoord.x][ActiveCoord.y + 2].status = BoardStatus::Empty;
					Board[ActiveCoord.x][ActiveCoord.y + 2].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 2].status,
							{ ActiveCoord.x,  ActiveCoord.y + 2 });
				}


			}

		}
		else {
			//for one step move-------------------------------------------------------------------
			if (ActiveCoord.y + 1 < 8) {
				if (Board[ActiveCoord.x][ActiveCoord.y + 1].status == BoardStatus::Highlighted) {
					Board[ActiveCoord.x][ActiveCoord.y + 1].status = BoardStatus::Empty;
					Board[ActiveCoord.x][ActiveCoord.y + 1].StatRect =
						StatusSpriteHandler(Board[ActiveCoord.x][ActiveCoord.y + 1].status,
							{ ActiveCoord.x,  ActiveCoord.y + 1 });
				}
			}
		}

		//capture for black----------------
		//left-diagonal
		if ((ActiveCoord.x - 1) >= 0 && (ActiveCoord.y + 1) < 8) {
			if (Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status == BoardStatus::Capture
				&&Board[ActiveCoord.x - 1][ActiveCoord.y + 1].piece->getPieceColor() == PieceColor::White) {
				Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status = BoardStatus::Occupied;
				Board[ActiveCoord.x - 1][ActiveCoord.y + 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x - 1][ActiveCoord.y + 1].status,
						{ ActiveCoord.x - 1,  ActiveCoord.y + 1 });
			}
		}
		//right-diagonal
		if ((ActiveCoord.x + 1) < 8 && (ActiveCoord.y + 1) < 8) {
			if (Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status == BoardStatus::Capture
				&&Board[ActiveCoord.x + 1][ActiveCoord.y + 1].piece->getPieceColor() == PieceColor::White) {
				Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status = BoardStatus::Occupied;
				Board[ActiveCoord.x + 1][ActiveCoord.y + 1].StatRect =
					StatusSpriteHandler(Board[ActiveCoord.x + 1][ActiveCoord.y + 1].status,
						{ ActiveCoord.x + 1,  ActiveCoord.y + 1 });
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
					Board[x - 1][y].status = BoardStatus::Capture;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
					break;
				}
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Empty) {
				Board[x - 1][y].status = BoardStatus::Highlighted;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
			x--;
			//}
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7) {
				//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) {
					Board[x + 1][y].status = BoardStatus::Capture;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
					break;
				}
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Empty) {
				Board[x + 1][y].status = BoardStatus::Highlighted;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
			x++;
			//}
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
			//if (y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x][y - 1].status = BoardStatus::Capture;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Empty) {
				Board[x][y - 1].status = BoardStatus::Highlighted;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
			y--;
			//}
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {
			//if (y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x][y + 1].status = BoardStatus::Capture;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Empty) {
				Board[x][y + 1].status = BoardStatus::Highlighted;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
			y++;
			//}
		}
	}

	


	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y].status == BoardStatus::Occupied) {
					if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) {
						Board[x - 1][y].status = BoardStatus::Capture;
						Board[x - 1][y].StatRect = StatusSpriteHandler(
							Board[x - 1][y].status, { x - 1, y });
						break;
					}
				}

				//if next field is empty
				if (Board[x - 1][y].status == BoardStatus::Empty) {
					Board[x - 1][y].status = BoardStatus::Highlighted;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
				}
				x--;
			//}
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y].status == BoardStatus::Occupied) {
					if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) {
						Board[x + 1][y].status = BoardStatus::Capture;
						Board[x + 1][y].StatRect = StatusSpriteHandler(
							Board[x + 1][y].status, { x + 1, y });
						break;
					}

				}

				//if next field is empty
				if (Board[x + 1][y].status == BoardStatus::Empty) {
					Board[x + 1][y].status = BoardStatus::Highlighted;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
				}
				x++;
			//}
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
			//if (y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x][y - 1].status == BoardStatus::Occupied) {
					if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) {
						Board[x][y - 1].status = BoardStatus::Capture;
						Board[x][y - 1].StatRect = StatusSpriteHandler(
							Board[x][y - 1].status, { x, y - 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x][y - 1].status == BoardStatus::Empty) {
					Board[x][y - 1].status = BoardStatus::Highlighted;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
				}
				y--;
			//}
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {
			//if (y + 1 >= 0 && y + 1 <= 7) {
				//if next field is empty
				if (Board[x][y + 1].status == BoardStatus::Empty) {
					Board[x][y + 1].status = BoardStatus::Highlighted;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
					
				}

				//if next field is occupied
				if (Board[x][y + 1].status == BoardStatus::Occupied) {
					if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) {
						Board[x][y + 1].status = BoardStatus::Capture;
						Board[x][y + 1].StatRect = StatusSpriteHandler(
							Board[x][y + 1].status, { x, y + 1 });
						break;
					}
				}
				y++;
			//}	
		}
	}

}

void Chessboard::HideRookPossibleMoves(sf::Vector2i ActiveCoord) {

	//tu w sumie tez moglbym pozmieniac te ify i dodac je do while'ow
	//ale to pozniej, na razie poki dziala niech zostanie

	//chociaz jednak zmienie aby mozna bylo skopiowac do queen

	//White---------------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x - 1][y].status == BoardStatus::Capture) {
				Board[x - 1][y].status = BoardStatus::Occupied;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Highlighted) {
				Board[x - 1][y].status = BoardStatus::Empty;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
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
				Board[x + 1][y].status = BoardStatus::Occupied;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Highlighted) {
				Board[x + 1][y].status = BoardStatus::Empty;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
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
				Board[x][y - 1].status = BoardStatus::Occupied;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Highlighted) {
				Board[x][y - 1].status = BoardStatus::Empty;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
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
				Board[x][y + 1].status = BoardStatus::Occupied;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Highlighted) {
				Board[x][y + 1].status = BoardStatus::Empty;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
			y++;
		}
	}




	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x > 0) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x - 1][y].status == BoardStatus::Capture) {
				Board[x - 1][y].status = BoardStatus::Occupied;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Highlighted) {
				Board[x - 1][y].status = BoardStatus::Empty;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
			x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x < 7) {

			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x + 1][y].status == BoardStatus::Capture) {
				Board[x + 1][y].status = BoardStatus::Occupied;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Highlighted) {
				Board[x + 1][y].status = BoardStatus::Empty;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
			x++;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y > 0) {

			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x][y - 1].status == BoardStatus::Capture) {
				Board[x][y - 1].status = BoardStatus::Occupied;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Highlighted) {
				Board[x][y - 1].status = BoardStatus::Empty;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
			y--;
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y < 7) {

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x][y + 1].status == BoardStatus::Capture) {
				Board[x][y + 1].status = BoardStatus::Occupied;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Highlighted) {
				Board[x][y + 1].status = BoardStatus::Empty;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
			y++;
		}

	}
}


//Knight show and hide--------------------------------------------------------
void Chessboard::ShowKnightPossibleMoves(sf::Vector2i ActiveCoord){

}

void Chessboard::HideKnightPossibleMoves(sf::Vector2i ActiveCoord){

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
			//if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
						Board[x - 1][y - 1].status = BoardStatus::Capture;
						Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
							Board[x - 1][y - 1].status, { x - 1, y - 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x - 1][y - 1].status == BoardStatus::Empty) {
					Board[x - 1][y - 1].status = BoardStatus::Highlighted;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
				}
				x--; y--;
			//}
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
						Board[x + 1][y - 1].status = BoardStatus::Capture;
						Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
							Board[x + 1][y - 1].status, { x + 1, y - 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x + 1][y - 1].status == BoardStatus::Empty) {
					Board[x + 1][y - 1].status = BoardStatus::Highlighted;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });
				}
				x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
						Board[x - 1][y + 1].status = BoardStatus::Capture;
						Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
							Board[x - 1][y + 1].status, { x - 1, y + 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x - 1][y + 1].status == BoardStatus::Empty) {
					Board[x - 1][y + 1].status = BoardStatus::Highlighted;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
				}
				x--; y++;
			//}
		}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
					else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
						Board[x + 1][y + 1].status = BoardStatus::Capture;
						Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
							Board[x + 1][y + 1].status, { x + 1, y + 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x + 1][y + 1].status == BoardStatus::Empty) {
					Board[x + 1][y + 1].status = BoardStatus::Highlighted;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
				}
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
			//if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) {
						Board[x - 1][y - 1].status = BoardStatus::Capture;
						Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
							Board[x - 1][y - 1].status, { x - 1, y - 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x - 1][y - 1].status == BoardStatus::Empty) {
					Board[x - 1][y - 1].status = BoardStatus::Highlighted;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
				}
				x--; y--;
			//}
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) {
						Board[x + 1][y - 1].status = BoardStatus::Capture;
						Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
							Board[x + 1][y - 1].status, { x + 1, y - 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x + 1][y - 1].status == BoardStatus::Empty) {
					Board[x + 1][y - 1].status = BoardStatus::Highlighted;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });
				}
				x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) {
						Board[x - 1][y + 1].status = BoardStatus::Capture;
						Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
							Board[x - 1][y + 1].status, { x - 1, y + 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x - 1][y + 1].status == BoardStatus::Empty) {
					Board[x - 1][y + 1].status = BoardStatus::Highlighted;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
				}
				x--; y++;
			}
		//}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied
				if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
					if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
					else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) {
						Board[x + 1][y + 1].status = BoardStatus::Capture;
						Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
							Board[x + 1][y + 1].status, { x + 1, y + 1 });
						break;
					}
				}

				//if next field is empty
				if (Board[x + 1][y + 1].status == BoardStatus::Empty) {
					Board[x + 1][y + 1].status = BoardStatus::Highlighted;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
				}
				x++; y++;
		//	}
		}
	}
}

void Chessboard::HideBishopPossibleMoves(sf::Vector2i ActiveCoord) {

	//White----------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
				Board[x - 1][y - 1].status = BoardStatus::Occupied;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y - 1].status = BoardStatus::Empty;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
			x--; y--;
			//}
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
				Board[x + 1][y - 1].status = BoardStatus::Occupied;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y - 1].status = BoardStatus::Empty;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
			x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;


		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
				//if next field is occupied

			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
			}

			else if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
				Board[x - 1][y + 1].status = BoardStatus::Occupied;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y + 1].status = BoardStatus::Empty;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
			x--; y++;
			//}
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
				Board[x + 1][y + 1].status = BoardStatus::Occupied;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y + 1].status = BoardStatus::Empty;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
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
			//if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
				Board[x - 1][y - 1].status = BoardStatus::Occupied;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y - 1].status = BoardStatus::Empty;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
			x--; y--;
			//}
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x + 1][y - 1].status == BoardStatus::Capture) {
				Board[x + 1][y - 1].status = BoardStatus::Occupied;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y - 1].status = BoardStatus::Empty;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
			x++; y--;
		}


		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
				Board[x - 1][y + 1].status = BoardStatus::Occupied;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y + 1].status = BoardStatus::Empty;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
			x--; y++;
		}
		//}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x + 1][y + 1].status == BoardStatus::Capture) {
				Board[x + 1][y + 1].status = BoardStatus::Occupied;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y + 1].status = BoardStatus::Empty;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
			x++; y++;
			//	}
		}
	}

}


//Queen show and hide---------------------------------------------------------
void Chessboard::ShowQueenPossibleMoves(sf::Vector2i ActiveCoord){
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
					Board[x - 1][y].status = BoardStatus::Capture;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
					break;
				}
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Empty) {
				Board[x - 1][y].status = BoardStatus::Highlighted;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
			x--;
			//}
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) {
					Board[x + 1][y].status = BoardStatus::Capture;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
					break;
				}
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Empty) {
				Board[x + 1][y].status = BoardStatus::Highlighted;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
			x++;
			//}
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
			//if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x][y - 1].status = BoardStatus::Capture;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Empty) {
				Board[x][y - 1].status = BoardStatus::Highlighted;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
			y--;
			//}
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {
			//if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x][y + 1].status = BoardStatus::Capture;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Empty) {
				Board[x][y + 1].status = BoardStatus::Highlighted;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
			y++;
			//}
		}

		x = ActiveCoord.x;
		y = ActiveCoord.y;
		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x - 1][y - 1].status = BoardStatus::Capture;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Empty) {
				Board[x - 1][y - 1].status = BoardStatus::Highlighted;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
			x--; y--;
			//}
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x + 1][y - 1].status = BoardStatus::Capture;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Empty) {
				Board[x + 1][y - 1].status = BoardStatus::Highlighted;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
			x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x - 1][y + 1].status = BoardStatus::Capture;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Empty) {
				Board[x - 1][y + 1].status = BoardStatus::Highlighted;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
			x--; y++;
			//}
		}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
				else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x + 1][y + 1].status = BoardStatus::Capture;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Empty) {
				Board[x + 1][y + 1].status = BoardStatus::Highlighted;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
			x++; y++;
			//}
		}
	}




	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) {
					Board[x - 1][y].status = BoardStatus::Capture;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
					break;
				}
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Empty) {
				Board[x - 1][y].status = BoardStatus::Highlighted;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
			x--;
			//}
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x + 1 >= 0 && x + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) {
					Board[x + 1][y].status = BoardStatus::Capture;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
					break;
				}

			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Empty) {
				Board[x + 1][y].status = BoardStatus::Highlighted;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
			x++;
			//}
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y - 1 >= 0 && y - 1 <= 7) {
			//if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) {
					Board[x][y - 1].status = BoardStatus::Capture;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Empty) {
				Board[x][y - 1].status = BoardStatus::Highlighted;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
			y--;
			//}
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y + 1 >= 0 && y + 1 <= 7) {
			//if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Empty) {
				Board[x][y + 1].status = BoardStatus::Highlighted;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });

			}

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) {
					Board[x][y + 1].status = BoardStatus::Capture;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
					break;
				}
			}
			y++;
			//}	
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
					Board[x - 1][y - 1].status = BoardStatus::Capture;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Empty) {
				Board[x - 1][y - 1].status = BoardStatus::Highlighted;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
			x--; y--;
			//}
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) {
					Board[x + 1][y - 1].status = BoardStatus::Capture;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Empty) {
				Board[x + 1][y - 1].status = BoardStatus::Highlighted;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
			x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					Board[x - 1][y + 1].status = BoardStatus::Capture;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Empty) {
				Board[x - 1][y + 1].status = BoardStatus::Highlighted;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
			x--; y++;
		}
		//}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;
				else if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					Board[x + 1][y + 1].status = BoardStatus::Capture;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
					break;
				}
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Empty) {
				Board[x + 1][y + 1].status = BoardStatus::Highlighted;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
			x++; y++;
			//	}
		}
	}
}

void Chessboard::HideQueenPossibleMoves(sf::Vector2i ActiveCoord){

	//White---------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x - 1][y].status == BoardStatus::Capture) {
				Board[x - 1][y].status = BoardStatus::Occupied;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Highlighted) {
				Board[x - 1][y].status = BoardStatus::Empty;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
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
				Board[x + 1][y].status = BoardStatus::Occupied;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Highlighted) {
				Board[x + 1][y].status = BoardStatus::Empty;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
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
				Board[x][y - 1].status = BoardStatus::Occupied;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Highlighted) {
				Board[x][y - 1].status = BoardStatus::Empty;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
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
				Board[x][y + 1].status = BoardStatus::Occupied;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Highlighted) {
				Board[x][y + 1].status = BoardStatus::Empty;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
			y++;
		}

		x = ActiveCoord.x;
		y = ActiveCoord.y;
		//top-left---------------
		while (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) break;

			}
			else if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
				Board[x - 1][y - 1].status = BoardStatus::Occupied;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y - 1].status = BoardStatus::Empty;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
			x--; y--;
			//}
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
				Board[x + 1][y - 1].status = BoardStatus::Occupied;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y - 1].status = BoardStatus::Empty;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
			x++; y--;
			//}
		}

		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;


		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied

			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) break;
			}

			else if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
				Board[x - 1][y + 1].status = BoardStatus::Occupied;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y + 1].status = BoardStatus::Empty;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
			x--; y++;
			//}
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
				Board[x + 1][y + 1].status = BoardStatus::Occupied;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y + 1].status = BoardStatus::Empty;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
			x++; y++;
			//}
		}

	}




	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		while (x > 0) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x - 1][y].status == BoardStatus::Capture) {
				Board[x - 1][y].status = BoardStatus::Occupied;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Highlighted) {
				Board[x - 1][y].status = BoardStatus::Empty;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
			x--;
		}

		//right
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (x < 7) {

			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x + 1][y].status == BoardStatus::Capture) {
				Board[x + 1][y].status = BoardStatus::Occupied;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Highlighted) {
				Board[x + 1][y].status = BoardStatus::Empty;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
			x++;
		}

		//up
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y > 0) {

			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x][y - 1].status == BoardStatus::Capture) {
				Board[x][y - 1].status = BoardStatus::Occupied;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Highlighted) {
				Board[x][y - 1].status = BoardStatus::Empty;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
			y--;
		}

		//down
		x = ActiveCoord.x;
		y = ActiveCoord.y;
		while (y < 7) {

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x][y + 1].status == BoardStatus::Capture) {
				Board[x][y + 1].status = BoardStatus::Occupied;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Highlighted) {
				Board[x][y + 1].status = BoardStatus::Empty;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
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

			}
			else if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
				Board[x - 1][y - 1].status = BoardStatus::Occupied;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y - 1].status = BoardStatus::Empty;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
			x--; y--;
			//}
		}

		//top-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x + 1][y - 1].status == BoardStatus::Capture) {
				Board[x + 1][y - 1].status = BoardStatus::Occupied;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y - 1].status = BoardStatus::Empty;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
			x++; y--;
		}


		//bottom-left---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
				Board[x - 1][y + 1].status = BoardStatus::Occupied;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y + 1].status = BoardStatus::Empty;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
			x--; y++;
		}
		//}

		//bottom-right---------------

		x = ActiveCoord.x;
		y = ActiveCoord.y;

		while (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) break;

			}
			else if (Board[x + 1][y + 1].status == BoardStatus::Capture) {
				Board[x + 1][y + 1].status = BoardStatus::Occupied;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
				break;
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y + 1].status = BoardStatus::Empty;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
			x++; y++;
			//	}
		}

	}
}


//King show and hide----------------------------------------------------------
void Chessboard::ShowKingPossibleMoves(sf::Vector2i ActiveCoord){

	//White---------------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::Black) {
					Board[x - 1][y].status = BoardStatus::Capture;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
				}
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Empty) {
				Board[x - 1][y].status = BoardStatus::Highlighted;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
		}

		//right
		if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::Black) {
					Board[x + 1][y].status = BoardStatus::Capture;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
				}
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Empty) {
				Board[x + 1][y].status = BoardStatus::Highlighted;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
		}

		//up
		if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x][y - 1].status = BoardStatus::Capture;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
				}
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Empty) {
				Board[x][y - 1].status = BoardStatus::Highlighted;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
		}

		//down
		if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x][y + 1].status = BoardStatus::Capture;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
				}
			}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Empty) {
				Board[x][y + 1].status = BoardStatus::Highlighted;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
		}

		//top-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x - 1][y - 1].status = BoardStatus::Capture;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
				}
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Empty) {
				Board[x - 1][y - 1].status = BoardStatus::Highlighted;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
		}

		//top-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x + 1][y - 1].status = BoardStatus::Capture;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });
				}
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Empty) {
				Board[x + 1][y - 1].status = BoardStatus::Highlighted;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
		}

		//bottom-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x - 1][y + 1].status = BoardStatus::Capture;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
				}
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Empty) {
				Board[x - 1][y + 1].status = BoardStatus::Highlighted;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
		}

		//bottom-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::Black) {
					Board[x + 1][y + 1].status = BoardStatus::Capture;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
				}
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Empty) {
				Board[x + 1][y + 1].status = BoardStatus::Highlighted;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
		}
	}




	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		
		//left---------------
		if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].piece->getPieceColor() == PieceColor::White) {
					Board[x - 1][y].status = BoardStatus::Capture;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
				}
			}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Empty) {
				Board[x - 1][y].status = BoardStatus::Highlighted;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
		}

		//right
		if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].piece->getPieceColor() == PieceColor::White) {
					Board[x + 1][y].status = BoardStatus::Capture;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
				}
			}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Empty) {
				Board[x + 1][y].status = BoardStatus::Highlighted;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
		}
		

		//down
		if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x][y - 1].status == BoardStatus::Occupied) {

				if (Board[x][y - 1].piece->getPieceColor() == PieceColor::White) {
					Board[x][y - 1].status = BoardStatus::Capture;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
				}
			}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Empty) {
				Board[x][y - 1].status = BoardStatus::Highlighted;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
		}

		//up
		if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Empty) {
				Board[x][y + 1].status = BoardStatus::Highlighted;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });

			}

			//if next field is occupied
			if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].piece->getPieceColor() == PieceColor::White) {
					Board[x][y + 1].status = BoardStatus::Capture;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
				}
			}
		}

		//top-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].piece->getPieceColor() == PieceColor::White) {
					Board[x - 1][y - 1].status = BoardStatus::Capture;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
				}
			}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Empty) {
				Board[x - 1][y - 1].status = BoardStatus::Highlighted;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
		}

		//top-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				 if (Board[x + 1][y - 1].piece->getPieceColor() == PieceColor::White) {
					Board[x + 1][y - 1].status = BoardStatus::Capture;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });

				 }
			}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Empty) {
				Board[x + 1][y - 1].status = BoardStatus::Highlighted;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
		}

		//bottom-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					Board[x - 1][y + 1].status = BoardStatus::Capture;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
				}
			}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Empty) {
				Board[x - 1][y + 1].status = BoardStatus::Highlighted;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
		}

		//bottom-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].piece->getPieceColor() == PieceColor::White) {
					Board[x + 1][y + 1].status = BoardStatus::Capture;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
				}
			}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Empty) {
				Board[x + 1][y + 1].status = BoardStatus::Highlighted;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
		}
	}
}

void Chessboard::HideKingPossibleMoves(sf::Vector2i ActiveCoord){
	//White---------------------------------------------------------------------------------
	if (Board[ActiveCoord.x][ActiveCoord.y].piece->getPieceColor() == PieceColor::White) {

		int x = ActiveCoord.x;
		int y = ActiveCoord.y;
		//left---------------
		if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			//if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].status == BoardStatus::Capture) {
					Board[x - 1][y].status = BoardStatus::Occupied;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
				}
			//}

			//if next field is empty
			if (Board[x - 1][y].status == BoardStatus::Highlighted) {
				Board[x - 1][y].status = BoardStatus::Empty;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
		}

		//right
		if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			//if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].status == BoardStatus::Capture) {
					Board[x + 1][y].status = BoardStatus::Occupied;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
				}
			//}

			//if next field is empty
			if (Board[x + 1][y].status == BoardStatus::Highlighted) {
				Board[x + 1][y].status = BoardStatus::Empty;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
		}

		//up
		if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			//if (Board[x][y - 1].status == BoardStatus::Occupied) {
				if (Board[x][y - 1].status == BoardStatus::Capture) {
					Board[x][y - 1].status = BoardStatus::Occupied;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
				}
			//}

			//if next field is empty
			if (Board[x][y - 1].status == BoardStatus::Highlighted) {
				Board[x][y - 1].status = BoardStatus::Empty;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
		}

		//down
		if (y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			//if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].status == BoardStatus::Capture) {
					Board[x][y + 1].status = BoardStatus::Occupied;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
				}
			//}

			//if next field is empty
			if (Board[x][y + 1].status == BoardStatus::Highlighted) {
				Board[x][y + 1].status = BoardStatus::Empty;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });
			}
		}

		//top-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			//if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
					Board[x - 1][y - 1].status = BoardStatus::Occupied;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
				}
			//}

			//if next field is empty
			if (Board[x - 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y - 1].status = BoardStatus::Empty;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
		}

		//top-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			//if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].status == BoardStatus::Capture) {
					Board[x + 1][y - 1].status = BoardStatus::Occupied;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });
				}
			//}

			//if next field is empty
			if (Board[x + 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y - 1].status = BoardStatus::Empty;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
		}

		//bottom-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			//if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
					Board[x - 1][y + 1].status = BoardStatus::Occupied;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
				}
			//}

			//if next field is empty
			if (Board[x - 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y + 1].status = BoardStatus::Empty;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
		}

		//bottom-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			//if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].status == BoardStatus::Capture) {
					Board[x + 1][y + 1].status = BoardStatus::Occupied;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
				}
			//}

			//if next field is empty
			if (Board[x + 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y + 1].status = BoardStatus::Empty;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
		}
	}




	//Black---------------------------------------------------------------------------------
	else {
		int x = ActiveCoord.x;
		int y = ActiveCoord.y;

		//left---------------
		if (x - 1 >= 0 && x - 1 <= 7) {
			//if next field is occupied
			//if (Board[x - 1][y].status == BoardStatus::Occupied) {
				if (Board[x - 1][y].status == BoardStatus::Capture) {
					Board[x - 1][y].status = BoardStatus::Occupied;
					Board[x - 1][y].StatRect = StatusSpriteHandler(
						Board[x - 1][y].status, { x - 1, y });
				} else if (Board[x - 1][y].status == BoardStatus::Occupied) {}
			//}

			//if next field is Highlighted
			if (Board[x - 1][y].status == BoardStatus::Highlighted) {
				Board[x - 1][y].status = BoardStatus::Empty;
				Board[x - 1][y].StatRect = StatusSpriteHandler(
					Board[x - 1][y].status, { x - 1, y });
			}
		}

		//right
		if (x + 1 >= 0 && x + 1 <= 7) {
			//if next field is occupied
			//if (Board[x + 1][y].status == BoardStatus::Occupied) {
				if (Board[x + 1][y].status == BoardStatus::Capture) {
					Board[x + 1][y].status = BoardStatus::Occupied;
					Board[x + 1][y].StatRect = StatusSpriteHandler(
						Board[x + 1][y].status, { x + 1, y });
				} else if (Board[x + 1][y].status == BoardStatus::Occupied) {}
			//}

			//if next field is Highlighted
			if (Board[x + 1][y].status == BoardStatus::Highlighted) {
				Board[x + 1][y].status = BoardStatus::Empty;
				Board[x + 1][y].StatRect = StatusSpriteHandler(
					Board[x + 1][y].status, { x + 1, y });
			}
		}


		//down
		if (y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			//if (Board[x][y - 1].status == BoardStatus::Occupied) {

				if (Board[x][y - 1].status == BoardStatus::Capture) {
					Board[x][y - 1].status = BoardStatus::Occupied;
					Board[x][y - 1].StatRect = StatusSpriteHandler(
						Board[x][y - 1].status, { x, y - 1 });
				} else if (Board[x][y - 1].status == BoardStatus::Occupied) {}
			//}

			//if next field is Highlighted
			if (Board[x][y - 1].status == BoardStatus::Highlighted) {
				Board[x][y - 1].status = BoardStatus::Empty;
				Board[x][y - 1].StatRect = StatusSpriteHandler(
					Board[x][y - 1].status, { x, y - 1 });
			}
		}

		//up
		if (y + 1 >= 0 && y + 1 <= 7) {
			

			//if next field is occupied
			//if (Board[x][y + 1].status == BoardStatus::Occupied) {
				if (Board[x][y + 1].status == BoardStatus::Capture) {
					Board[x][y + 1].status = BoardStatus::Occupied;
					Board[x][y + 1].StatRect = StatusSpriteHandler(
						Board[x][y + 1].status, { x, y + 1 });
				} else if (Board[x][y + 1].status == BoardStatus::Occupied) {}
			//}
			
			//if next field is Highlighted
			if (Board[x][y + 1].status == BoardStatus::Highlighted) {
				Board[x][y + 1].status = BoardStatus::Empty;
				Board[x][y + 1].StatRect = StatusSpriteHandler(
					Board[x][y + 1].status, { x, y + 1 });

			}

		}

		//top-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			//if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y - 1].status == BoardStatus::Capture) {
					Board[x - 1][y - 1].status = BoardStatus::Occupied;
					Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y - 1].status, { x - 1, y - 1 });
				} else if (Board[x - 1][y - 1].status == BoardStatus::Occupied) {}
			//}

			//if next field is Highlighted
			if (Board[x - 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y - 1].status = BoardStatus::Empty;
				Board[x - 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y - 1].status, { x - 1, y - 1 });
			}
		}

		//top-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y - 1 >= 0 && y - 1 <= 7) {
			//if next field is occupied
			//if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y - 1].status == BoardStatus::Capture) {
					Board[x + 1][y - 1].status = BoardStatus::Occupied;
					Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y - 1].status, { x + 1, y - 1 });
				} else if (Board[x + 1][y - 1].status == BoardStatus::Occupied) {}
			//}

			//if next field is Highlighted
			if (Board[x + 1][y - 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y - 1].status = BoardStatus::Empty;
				Board[x + 1][y - 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y - 1].status, { x + 1, y - 1 });
			}
		}

		//bottom-left---------------
		if (x - 1 >= 0 && x - 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			//if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x - 1][y + 1].status == BoardStatus::Capture) {
					Board[x - 1][y + 1].status = BoardStatus::Occupied;
					Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x - 1][y + 1].status, { x - 1, y + 1 });
				} else if (Board[x - 1][y + 1].status == BoardStatus::Occupied) {}
			//}

			//if next field is Highlighted
			if (Board[x - 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x - 1][y + 1].status = BoardStatus::Empty;
				Board[x - 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x - 1][y + 1].status, { x - 1, y + 1 });
			}
		}

		//bottom-right---------------
		if (x + 1 >= 0 && x + 1 <= 7 && y + 1 >= 0 && y + 1 <= 7) {
			//if next field is occupied
			//if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {
				if (Board[x + 1][y + 1].status == BoardStatus::Capture) {
					Board[x + 1][y + 1].status = BoardStatus::Occupied;
					Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
						Board[x + 1][y + 1].status, { x + 1, y + 1 });
				} else if (Board[x + 1][y + 1].status == BoardStatus::Occupied) {}
			//}

			//if next field is Highlighted
			if (Board[x + 1][y + 1].status == BoardStatus::Highlighted) {
				Board[x + 1][y + 1].status = BoardStatus::Empty;
				Board[x + 1][y + 1].StatRect = StatusSpriteHandler(
					Board[x + 1][y + 1].status, { x + 1, y + 1 });
			}
		}
	}
}
