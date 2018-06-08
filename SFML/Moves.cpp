#include "Chessboard.h"

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

		}
		else {
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
			ChangeStatusForHighlighted(x, y + 1);
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
void Chessboard::ShowKnightPossibleMoves(sf::Vector2i ActiveCoord) {

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
		if ((x + 1 <= 7 && y - 2 >= 0)) {

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

void Chessboard::HideKnightPossibleMoves(sf::Vector2i ActiveCoord) {
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
void Chessboard::ShowQueenPossibleMoves(sf::Vector2i ActiveCoord) {
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
void Chessboard::ShowKingPossibleMoves(sf::Vector2i ActiveCoord) {

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
					if (!CheckIfFieldIsAttacked({ x - 1, y }, PieceColor::White))
						ChangeStatusForCapture(x - 1, y);
				}
			}
			else if (!CheckIfFieldIsAttacked({ x - 1, y }, PieceColor::White))
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
			}
			else if (!CheckIfFieldIsAttacked({ x + 1, y }, PieceColor::White))
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
			}
			else if (!CheckIfFieldIsAttacked({ x, y - 1 }, PieceColor::White))
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
			}
			else if (!CheckIfFieldIsAttacked({ x, y + 1 }, PieceColor::White))
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
			}
			else if (!CheckIfFieldIsAttacked({ x - 1, y - 1 }, PieceColor::White))
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
			}
			else if (!CheckIfFieldIsAttacked({ x + 1, y - 1 }, PieceColor::White))
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
			}
			else if (!CheckIfFieldIsAttacked({ x - 1, y + 1 }, PieceColor::White))
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
			}
			else if (!CheckIfFieldIsAttacked({ x + 1, y + 1 }, PieceColor::White))
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
					if (!CheckIfFieldIsAttacked({ x - 1, y }, PieceColor::Black))
						ChangeStatusForCapture(x - 1, y);
				}
			}
			else if (!CheckIfFieldIsAttacked({ x - 1, y }, PieceColor::Black))
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
			}
			else if (!CheckIfFieldIsAttacked({ x + 1, y }, PieceColor::Black))
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
			}
			else if (!CheckIfFieldIsAttacked({ x, y + 1 }, PieceColor::Black))
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
			}
			else if (!CheckIfFieldIsAttacked({ x, y - 1 }, PieceColor::Black))
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
			}
			else if (!CheckIfFieldIsAttacked({ x - 1, y - 1 }, PieceColor::Black))
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
			}
			else if (!CheckIfFieldIsAttacked({ x + 1, y - 1 }, PieceColor::Black))
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
			}
			else if (!CheckIfFieldIsAttacked({ x - 1, y + 1 }, PieceColor::Black))
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
			}
			else if (!CheckIfFieldIsAttacked({ x + 1, y + 1 }, PieceColor::Black))
				ChangeStatusForHighlighted(x + 1, y + 1);

			//if next field is empty

		}
	}
}

void Chessboard::HideKingPossibleMoves(sf::Vector2i ActiveCoord) {
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
