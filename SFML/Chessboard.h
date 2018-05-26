#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <array>
#include <iostream>
#include <map>
#include "Chesspiece.h"
#include "Pawn.h"
#include "Useful.h"

using PiecePtr = std::shared_ptr<ChessPiece>;
//using PieceSet = std::array<std::shared_ptr<ChessPiece>, 16>;
using PieceSet = std::vector<std::shared_ptr<ChessPiece>>;


class Chessboard
{
public:
	struct BoardSlot {
		sf::Sprite rect;
		sf::Sprite StatRect;
		std::shared_ptr<ChessPiece> piece;
		BoardStatus status;
	};

private:
	std::array<std::array<BoardSlot, 8>, 8> Board;
	PieceSet WhitePiecesSet;
	PieceSet BlackPiecesSet;

	sf::Texture t_background;
	sf::Sprite background;

	std::map<std::string, sf::Texture> TextureMap;

	void Sprites();

	//Chess pieces possible moves
		//Pawn
		void ShowPawnPossibleMoves(sf::Vector2i ActiveCoord);
		void HidePawnPossibleMoves(sf::Vector2i ActiveCoord);
		//Rook
		void ShowRookPossibleMoves(sf::Vector2i ActiveCoord);
		void HideRookPossibleMoves(sf::Vector2i ActiveCoord);
		//Knight
		void ShowKnightPossibleMoves(sf::Vector2i ActiveCoord);
		void HideKnightPossibleMoves(sf::Vector2i ActiveCoord);
		//Bishop
		void ShowBishopPossibleMoves(sf::Vector2i ActiveCoord);
		void HideBishopPossibleMoves(sf::Vector2i ActiveCoord);
		//Queen
		void ShowQueenPossibleMoves(sf::Vector2i ActiveCoord);
		void HideQueenPossibleMoves(sf::Vector2i ActiveCoord);
		//King
		void ShowKingPossibleMoves(sf::Vector2i ActiveCoord);
		void HideKingPossibleMoves(sf::Vector2i ActiveCoord);
public:

	Chessboard();
	~Chessboard();

	//Move and possible moves
	void Move(sf::Vector2i ActiveCoord, sf::Vector2i NewCoord);
	void Capture(sf::Vector2i ActiveCoord, sf::Vector2i CurrentCoord);
	void ShowPossibleMoves(sf::Vector2i ActiveCoord);
	void HidePossibleMoves(sf::Vector2i ActiveCoord);



	//Get
	BoardStatus getBoardStatus(sf::Vector2i coor);
	std::array<std::array<BoardSlot, 8>, 8> getBoard() { return Board; }
	PieceColor getPieceColor(sf::Vector2i coor);

	//Change
	void MakeActiveSprite(sf::Vector2i coord);
	void UnmakeActiveSprite(sf::Vector2i coord);

	//Sprite Handlers
	sf::Sprite StatusSpriteHandler(BoardStatus status, sf::Vector2i coord);
	sf::Sprite PieceSpriteHandler(PieceID id, PieceColor color, sf::Vector2i coord);

	void Initialize();
	void Render(sf::RenderWindow& l_window);
};

