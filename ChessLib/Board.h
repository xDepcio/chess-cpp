#pragma once
#include "Piece.h"
#include "Square.h"
#include <vector>
#include <iostream>

class Board
{
public:
	Board(int width, int height)
	{
		for (int j = 0; j < height; j++)
		{
			squares.push_back(std::vector<Square>());
			for (int i = 0; i < width; i++)
			{
				squares[j].push_back(Square());
			}
		}
	}

	void setPiece(std::pair<int, int> cords, Piece piece)
	{
		squares[cords.first][cords.second].setPiece(piece);
	}

	std::vector<std::vector<Square> >& getBoard()
	{
		return squares;
	}

	void printBoard()
	{
		for (int i = 0; i < squares.size(); i++)
		{
			for (int j = 0; j < squares[0].size(); j++)
			{
				std::cout << " X ";
			}
			std::cout << '\n';
		}
	}

private:
	std::vector<std::vector<Square> > squares = { };
};
