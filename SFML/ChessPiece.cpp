#include "ChessPiece.h"



ChessPiece::ChessPiece()
{
}

ChessPiece::ChessPiece(PieceColor s_color, sf::Sprite s_whiteSprite, PieceID s_id, sf::Vector2i s_position) {
	color = s_color;
	whiteSprite = s_whiteSprite;
	id = s_id;
	position = s_position;
	moveCount = 0;
}


ChessPiece::~ChessPiece()
{
}

PieceColor ChessPiece::getPieceColor() {
	return color;
}

PieceID ChessPiece::getPieceID() {
	return id;
}

sf::Sprite ChessPiece::getWhitePieceSprite() {
	return whiteSprite;
}

sf::Sprite ChessPiece::getBlackPieceSprite() {
	return blackSprite;
}

int ChessPiece::getMoveCount() {
	return moveCount;
}

void ChessPiece::setPosition(sf::Vector2i coord) {
	position = coord;
}

void ChessPiece::increamentMoveCount() {
	moveCount++;
}
