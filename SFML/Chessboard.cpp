#include "Chessboard.h"

void Chessboard::Sprites() {
	
	sf::Texture temp;
	
	//White
	if (temp.loadFromFile("Assets/Textures/Pieces/wP.png"))
		TextureMap["wP"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/wR.png"))
		TextureMap["wR"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/wKn.png"))
		TextureMap["wKn"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/wB.png"))
		TextureMap["wB"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/wQ.png"))
		TextureMap["wQ"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/wK.png"))
		TextureMap["wK"]=temp; else std::cout << "why?\n";
	
	//Black
	if (temp.loadFromFile("Assets/Textures/Pieces/bP.png"))
		TextureMap["bP"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/bR.png"))
		TextureMap["bR"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/bKn.png"))
		TextureMap["bKn"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/bB.png"))
		TextureMap["bB"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/bQ.png"))
		TextureMap["bQ"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Pieces/bK.png"))
		TextureMap["bK"]=temp; else std::cout << "why?\n";

	//Other
	if (temp.loadFromFile("Assets/Textures/Status/blue.png"))
		TextureMap["blue"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Status/high.png"))
		TextureMap["green"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Status/capt.png"))
		TextureMap["red"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("Assets/Textures/Status/none.png"))
		TextureMap["none"] = temp; else std::cout << "none?\n";

	if (temp.loadFromFile("Assets/Textures/Buttons/i_draw.png"))
		TextureMap["draw"] = temp; else std::cout << "draw?\n";

	if (temp.loadFromFile("Assets/Textures/Buttons/i_surrender.png"))
		TextureMap["surrender"] = temp; else std::cout << "surrender?\n";

	if (temp.loadFromFile("Assets/Textures/Status/turns.png"))
		TextureMap["turns"] = temp; else std::cout << "turns?\n";

	if (temp.loadFromFile("Assets/Textures/Buttons/i_gdraw.png"))
		TextureMap["acc"] = temp; else std::cout << "accept?\n";

	if (temp.loadFromFile("Assets/Textures/Buttons/i_rdraw.png"))
		TextureMap["dec"] = temp; else std::cout << "dec?\n";


	if (t_background.loadFromFile("Assets/Textures/Menus/Chessboard.png"))
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
	//Sounds();
	Initialize();
}
Chessboard::~Chessboard() = default;

//Move
void Chessboard::Move(sf::Vector2i ActiveCoord, sf::Vector2i NewCoord){
	//audio.play("move");
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
	//audio.play("capture");

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
		//audio.play("promotion");
		Board[coord.x][coord.y].piece->setPieceIDforPromotion(id);
		Board[coord.x][coord.y].rect = PieceSpriteHandler(Board[coord.x][coord.y].piece->getPieceID(),
			Board[coord.x][coord.y].piece->getPieceColor(), coord);
		promotion = false;
}

void Chessboard::ShortCastle(PieceColor color) {
	//audio.play("castle");
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
	//audio.play("castle");
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
	//audio.play("active");
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
	//audio.play("unactive");
	Board[coord.x][coord.y].status = BoardStatus::Occupied;
	Board[coord.x][coord.y].StatRect = StatusSpriteHandler(Board[coord.x][coord.y].status, coord);
	HidePossibleMoves(coord);
}

void Chessboard::ChangeTurnSprite(PieceColor color) {
	if (color == PieceColor::Black) {	
		Turn.setPosition(720, 112);
	} else {
		Turn.setPosition(720, 585);
	}
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

void Chessboard::RenderDraw() {
	draw = true;
	acc.setTexture(TextureMap["acc"]);
	dec.setTexture(TextureMap["dec"]);

	acc.setPosition(833 + 84, 318);
	dec.setPosition(833 + 84 * 2, 318);
}

void Chessboard::Initialize() {

	draw = false;

	Draw0.setTexture(TextureMap["draw"]);
	Draw0.setPosition(846, 96);
	Draw1.setTexture(TextureMap["draw"]);
	Draw1.setPosition(846, 569);

	Surr0.setTexture(TextureMap["surrender"]);
	Surr0.setPosition(1090, 96);
	Surr1.setTexture(TextureMap["surrender"]);
	Surr1.setPosition(1090, 569);

	Turn.setTexture((TextureMap["turns"]));
	Turn.setPosition(720, 585);



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
		
	}
	if (promotion == true) {
		l_window.draw(rook);
		l_window.draw(knight);
		l_window.draw(bishop);
		l_window.draw(queen);
	}

	if (promotion==false&&draw==true) {
		l_window.draw(acc);
		l_window.draw(dec);
	}

	l_window.draw(Draw0);
	l_window.draw(Draw1);
	l_window.draw(Surr0);
	l_window.draw(Surr1);
	l_window.draw(Turn);

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

