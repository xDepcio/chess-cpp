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

std::unique_ptr<Piece> Board::setPiece(std::pair<int, int> cords, std::unique_ptr<Piece> piece)
{
	return squares[cords.first][cords.second].setPiece(std::move(piece));
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
			Piece* squarePiece = squares[i][j].getPiece();
			if (squarePiece != nullptr)
			{
				std::cout << ' ' << squarePiece->getName() << ' ';
			}
			else
			{
				std::cout << " - ";
			}
		}
		std::cout << '\n';
	}
}

void Board::move(std::pair<int, int> from, std::pair<int, int> to)
{
	if (squares[from.first][from.second].getPiece()->isMoveValid(this, from, to))
	{
		setPiece(to, setPiece(from, nullptr));
	}
}
