#include "ChessPiece.h"



ChessPiece::ChessPiece()
{
}

ChessPiece::ChessPiece(PieceColor s_color, PieceID s_id, sf::Vector2i s_position, std::string s_sn) {
	color = s_color;
	id = s_id;
	position = s_position;
	spriteName = s_sn;
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

std::string ChessPiece::getSpriteName()
{
	return spriteName;
}

//sf::Sprite ChessPiece::getWhitePieceSprite() {
//	return whiteSprite;
//}
//
//sf::Sprite ChessPiece::getBlackPieceSprite() {
//	return blackSprite;
//}

int ChessPiece::getMoveCount() {
	return moveCount;
}

void ChessPiece::setPosition(sf::Vector2i coord) {
	position = coord;
}

void ChessPiece::increamentMoveCount() {
	moveCount++;
}
