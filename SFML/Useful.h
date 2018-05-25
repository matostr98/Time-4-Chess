#pragma once
#include <memory>
#include "ChessPiece.h"

enum class BoardStatus { Empty, Occupied, Active, Highlighted, Capture };
enum class PieceColor { White, Black };
enum class PieceID { Pawn, Rook, Knight, Bishop, Queen, King };

