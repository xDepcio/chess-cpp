#pragma once
#include "Piece.h"
#include "Square.h"
#include <vector>

class Board
{
public:
	Board()
	{
		squares.push_back(std::vector<Square>());
		squares.push_back(std::vector<Square>());
		squares[0].push_back(Square());
		squares[0].push_back(Square());
		squares[1].push_back(Square());
		squares[1].push_back(Square());
	}

	void setPiece(Square& square, Piece& piece)
	{
		square.setPiece(piece);
	}

	std::vector<std::vector<Square> >& getBoard()
	{
		return squares;
	}

private:
	std::vector<std::vector<Square> > squares = { };
};
