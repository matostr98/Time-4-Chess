#pragma once
//#include <map>
#include "ChessPiece.h"

enum class BoardStatus { Empty, Occupied, Active, Highlighted, Capture };
enum class PieceColor { White, Black };
enum class PieceID { Pawn, Rook, Knight, Bishop, Queen, King };

//std::map<std::string, sf::Sprite> SpriteMap;