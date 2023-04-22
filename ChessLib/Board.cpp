#include "Board.h"

void Board::setPiece(Piece const& piece, std::pair<int, int> cords)
{
	squares[cords.first][cords.second].setPiece(piece);
}

Board::Board()
{
	squares = {
		{ Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black) },
		{ Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White) },
		{ Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black) },
		{ Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White) },
		{ Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black) },
		{ Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White) },
		{ Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black) },
		{ Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White), Square(Color::Black), Square(Color::White) },
	};
}

Board::Board(std::vector<std::vector<Square>> startingPlacement)
{
	squares = startingPlacement;
}
