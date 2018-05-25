#pragma once
#include "ChessPiece.h"
class Pawn :
	public ChessPiece
{
public:
	Pawn(PieceColor s_color, sf::Vector2i s_position);
	~Pawn();

	virtual std::vector<sf::Vector2i> getPossibleMoves(
		/*std::array<std::array<Chessboard::BoardSlot, 8>, 8> Board*/) override;
};

