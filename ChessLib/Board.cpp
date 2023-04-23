#include "Board.h"

Board::Board(int width, int height)
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

void Board::setPiece(std::pair<int, int> cords, Piece piece)
{
	squares[cords.first][cords.second].setPiece(piece);
}

std::vector<std::vector<Square>>& Board::getBoard()
{
	return squares;
}

void Board::printBoard() const
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

void Board::move(std::pair<int, int> from, std::pair<int, int> to)
{
	Piece* movedPiece = squares[from.first][from.second].getPiece();
	if (movedPiece->isMoveValid(this, from, to))
	{
		Piece r = *movedPiece;
		squares[to.first][to.second].setPiece(r);
	}
}
