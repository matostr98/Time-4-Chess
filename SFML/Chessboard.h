#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <array>
#include <iostream>
#include <map>
#include "Chesspiece.h"
#include "Pawn.h"
#include "Useful.h"

using PiecePtr = std::shared_ptr<ChessPiece>;
//using PieceSet = std::array<std::shared_ptr<ChessPiece>, 16>;
//using PieceSet = std::vector<std::shared_ptr<ChessPiece>>;


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

	sf::Texture t_background;
	sf::Sprite background;

	sf::Sprite rook;
	sf::Sprite knight;
	sf::Sprite bishop;
	sf::Sprite queen;
	sf::Sprite Draw0;
	sf::Sprite Draw1;
	sf::Sprite Surr0;
	sf::Sprite Surr1;
	sf::Sprite Turn;

	//Booleans
	bool promotion;
	bool WhiteCastle;
	bool BlackCastle;

	//maps
	std::map<std::string, sf::Texture> TextureMap;
	std::map<std::string, sf::SoundBuffer> SFXMap;


	//king positions 
	sf::Vector2i WhiteKingCoordinates;
	sf::Vector2i BlackKingCoordinates;

	sf::Vector2i PreviousCoordinates;

	void Sprites();
	void Sounds();
	void setPiece(PieceColor color, PieceID id, sf::Vector2i coord);

	//Chess pieces show and hide functions
		//moze to zrobie exeptions pozniej
		void ChangeStatusForHighlighted(int x, int y);
		void ChangeStatusForCapture(int x, int y);

		void ChangeStatusToOccupied(int x, int y);
		void ChangeStatusToEmpty(int x, int y);
		
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

	//Checking whether the field is being attacked
	bool CheckIfFieldIsAttacked(sf::Vector2i Coord, PieceColor color);
	bool CheckOneRookAttack(PieceColor color, sf::Vector2i Coord);
	bool CheckOneBishopAttack(PieceColor color, sf::Vector2i Coord);
	bool CheckOneKnightAttack(PieceColor color, sf::Vector2i Coord);
	bool CheckOneKingAttack(PieceColor color, sf::Vector2i Coord);
	bool CheckOnePawnAttack(PieceColor color, sf::Vector2i Coord);

	//Special moves
	void Promotion(PieceID id, sf::Vector2i coord);
	void ShortCastle(PieceColor color);
	void LongCastle(PieceColor color);
	void EnPassant(sf::Vector2i ActiveCoord, sf::Vector2i NewCoord, PieceColor color);

	//Show special moves
	void ShowShortCastle(PieceColor color);
	void ShowLongCastle(PieceColor color);

	//checkmate
	bool CheckForCheck();
	bool CheckForCheckmate();
	PieceColor check;

	//Get
	BoardStatus getBoardStatus(sf::Vector2i coor);
	std::array<std::array<BoardSlot, 8>, 8> getBoard() { return Board; }
	PieceColor getPieceColor(sf::Vector2i coor);
	PieceID getPieceID(sf::Vector2i coor);
	bool getNullPtr(sf::Vector2i coor);

	//Change
	void MakeActiveSprite(sf::Vector2i coord);
	//void MakeActiveKingSprite(sf::Vector2i Coord);
	void UnmakeActiveSprite(sf::Vector2i coord);
	void ChangeTurnSprite(PieceColor color);

	//Sprite Handlers
	sf::Sprite StatusSpriteHandler(BoardStatus status, sf::Vector2i coord);
	sf::Sprite PieceSpriteHandler(PieceID id, PieceColor color, sf::Vector2i coord);
	sf::Sprite PromotionSpriteHandler(PieceColor color, int n);

	

	void Initialize();
	void Render(sf::RenderWindow& l_window);
	void RenderPromotion(PieceColor color);
};

