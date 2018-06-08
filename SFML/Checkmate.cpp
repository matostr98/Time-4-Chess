#include "Chessboard.h"

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


bool Chessboard::CheckForCheck() {
	if (CheckIfFieldIsAttacked(WhiteKingCoordinates, PieceColor::White)) {
		check = PieceColor::White;
		//audio.play("check");
		return true;
	}
	if (CheckIfFieldIsAttacked(BlackKingCoordinates, PieceColor::Black)) {
		check = PieceColor::Black;
		//audio.play("check");
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

		if (WhiteKingCoordinates.x - 1 >= 0 && WhiteKingCoordinates.x - 1 <= 7 &&
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
	else if (check == PieceColor::Black) {

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

	//audio.play("checkmate");
	return true;
}
