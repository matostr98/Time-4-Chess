#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Useful.h"
//#include "Chessboard.h"




class ChessPiece
{
protected:

	PieceColor color;
	sf::Sprite whiteSprite;
	sf::Sprite blackSprite;
	PieceID id;

	sf::Vector2i position;
	int moveCount;
public:
	ChessPiece();
	ChessPiece(PieceColor s_color, sf::Sprite s_whiteSprite, PieceID s_id, sf::Vector2i s_position);
	~ChessPiece();

	//Get
	PieceColor getPieceColor();
	PieceID getPieceID();
	sf::Sprite getWhitePieceSprite();
	sf::Sprite getBlackPieceSprite();
	int getMoveCount();


	//Set
	void setPosition(sf::Vector2i coord);
	void increamentMoveCount();

	//Virtual
	//virtual std::vector<sf::Vector2i> getPossibleMoves() = 0;

};

