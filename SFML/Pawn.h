#pragma once
#include "ChessPiece.h"
class Pawn :
	public ChessPiece
{
public:
	Pawn(PieceColor s_color, sf::Sprite s_whiteSprite, PieceID s_id, sf::Vector2i s_position);
	~Pawn();

	//std::vector<sf::Vector2i> getPossibleMoves() override;
};

