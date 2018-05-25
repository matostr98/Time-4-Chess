#pragma once
#include <string>
//#include "ChessPiece.h"

enum class BoardStatus { Empty, Occupied, Active, Highlighted, Capture };
enum class PieceColor { White, Black };
enum class PieceID { Pawn, Rook, Knight, Bishop, Queen, King };

////Strings
//	//White Pieces
//		std::string wP{ "wP" };
//		std::string wR{ "wR" };
//		std::string wKn{"wKn"};
//		std::string wB{ "wB" };
//		std::string wQ{ "wQ" };
//		std::string wK{ "wK" };
//	//Black Pieces
//		std::string bP = "bP";
//		std::string bR = "bR";
//		std::string bKn = "bKn";
//		std::string bB = "bB";
//		std::string bQ = "bQ";
//		std::string bK = "bK";
//	//Other
//		std::string blue = "blue";
//		std::string green = "green";
//		std::string red = "red";