#pragma once
#include "ChessPiece.h"
class Pawn :
	public ChessPiece
{
public:
	Pawn(PieceColor s_color, PieceID s_id, sf::Vector2i s_position);
	~Pawn();

	virtual std::vector<sf::Vector2i> getPossibleMoves() override;
};

