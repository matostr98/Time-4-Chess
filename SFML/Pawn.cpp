#include "Pawn.h"



Pawn::Pawn(PieceColor s_color, PieceID s_id, sf::Vector2i s_position) 
	:ChessPiece(s_color, s_id, s_position) {

}


Pawn::~Pawn()
{
}

std::vector<sf::Vector2i> Pawn::getPossibleMoves(
	/*std::array<std::array<Chessboard::BoardSlot, 8>, 8> Board*/)
{
	std::vector<sf::Vector2i> moves;
	//no capture!!!!!
	if (color == PieceColor::White) {
		if (moveCount == 0) {
			moves.push_back({ position.x, position.y + 1 });
			moves.push_back({ position.x, position.y + 2 });
		}
		else {
			moves.push_back({ position.x, position.y + 1 });
		}
	}
	else {
		if (moveCount == 0) {
			moves.push_back({ position.x, position.y - 1 });
			moves.push_back({ position.x, position.y - 2 });
		}
		else {
			moves.push_back({ position.x, position.y - 1 });
		}
	}
	return moves;
}




