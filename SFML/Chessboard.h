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
	void ShowPawnPossibleMoves();
	void HidePawnPossibleMoves();

public:

	Chessboard();
	~Chessboard();

	//Move and possible moves
	void Move(sf::Vector2i ActiveCoord, sf::Vector2i CurrentCoord);
	void Capture(sf::Vector2i ActiveCoord, sf::Vector2i CurrentCoord);
	void ShowPossibleMoves(sf::Vector2i ActiveCoord);
	void HidePossibleMoves(sf::Vector2i ActiveCoord);



	//Get
	BoardStatus getBoardStatus(sf::Vector2i coor);
	std::array<std::array<BoardSlot, 8>, 8> getBoard() { return Board; }

	//Change
	void MakeActiveSprite(sf::Vector2i coord);
	void UnmakeActiveSprite(sf::Vector2i coord);

	//Sprite Handlers
	sf::Sprite StatusSpriteHandler(BoardStatus status, sf::Vector2i coord);
	sf::Sprite PieceSpriteHandler(PieceID id, PieceColor color, sf::Vector2i coord);

	void Initialize();
	void Render(sf::RenderWindow& l_window);
};

