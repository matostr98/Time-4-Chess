#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Useful.h"
#include <array>
//#include "Chessboard.h"




class ChessPiece
{
protected:
	struct BoardSlot {
		sf::Sprite rect;
		std::shared_ptr<ChessPiece> piece;
		BoardStatus status;
	};

	PieceColor color;
	/*sf::Sprite whiteSprite;
	sf::Sprite blackSprite;*/
	std::string spriteName;
	PieceID id;

	sf::Vector2i position;
	int moveCount;
public:
	//Constructors and destructors
	ChessPiece();
	ChessPiece(PieceColor s_color,
		sf::Vector2i s_position);
	~ChessPiece();

	//Get
	PieceColor getPieceColor();
	PieceID getPieceID();
	std::string getSpriteName();
	/*sf::Sprite getWhitePieceSprite();
	sf::Sprite getBlackPieceSprite();*/
	int getMoveCount();


	//Set
	void setPosition(sf::Vector2i coord);
	void increamentMoveCount();

	//Virtual
	virtual std::vector<sf::Vector2i> getPossibleMoves(
		std::array<std::array<BoardSlot, 8>, 8> &Board) = 0;

};

