#pragma once
#include <iostream>
#include <vector>
//#include "../../../../../Chess/ChessLib/Board.h"
//#include "../../../../../Chess/ChessLib/Bishop.h"
//#include "../../../../../Chess/ChessLib/King.h"
//#include "../../../../../Chess/ChessLib/Knight.h"
//#include "../../../../../Chess/ChessLib/Pawn.h"
//#include "../../../../../Chess/ChessLib/Piece.h"
//#include "../../../../../Chess/ChessLib/Queen.h"

class Piece;
class Board;
class Square;

class QtGame
{
private:
	Board* trackedBoard;
	Piece* clickedPiece;
	std::pair<int, int> clickedPieceCoords;

public:
	QtGame() : trackedBoard(nullptr), clickedPiece(nullptr), clickedPieceCoords({}) {};

	void setupBoard();
	void run();

	Piece* getPieceAtCoords(std::pair<int, int> const& coords) const;
	
	std::vector<std::vector<Square> >& getSquares();

	bool isMoveValid(std::pair<int, int> const& from, std::pair<int, int> const& to);

	void move(std::pair<int, int> const& from, std::pair<int, int> const& to);

	void setClickedPiece(Piece* piece);
	void setClickedPieceCoords(std::pair<int, int> const& coords);

	Piece* getClickedPiece() const;
	std::pair<int, int> getClickedPieceCoords() const;

	Board* getBoard() const;
};

