#pragma once
#include "../../../../../Chess/ChessLib/Board.h"
#include "../../../../../Chess/ChessLib/Bishop.h"
#include "../../../../../Chess/ChessLib/King.h"
#include "../../../../../Chess/ChessLib/Knight.h"
#include "../../../../../Chess/ChessLib/Pawn.h"
#include "../../../../../Chess/ChessLib/Piece.h"
#include "../../../../../Chess/ChessLib/Queen.h"

class QtGame
{
private:
	Board* trackedBoard;
public:
	QtGame() : trackedBoard(nullptr) {};

	void setupBoard();
	void run();
};

