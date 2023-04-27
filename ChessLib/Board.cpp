#include "Board.h"

Board::Board(int width, int height)
{
	this->width = width;
	this->height = height;

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
	// returns Piece which prevoisly occupied square at coords
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
				std::cout << " -- ";
			}
		}
		std::cout << '\n';
	}
}

Piece* Board::getPiece(std::pair<int, int> coords) const
{
	return squares[coords.first][coords.second].getPiece();
}

std::vector<std::pair<int, int>> Board::getPawnMoves(std::pair<int, int> atCoords)
{
	Pawn* pieceAtCoords = dynamic_cast<Pawn*>(getPiece(atCoords));
	int dir = pieceAtCoords->getColor() == Piece::Color::White ? 1 : -1;

	std::vector<std::pair<int, int>> validMoves;
	std::vector<std::pair<int, int>> takesToCheck = {
		{atCoords.first-(1*dir), atCoords.second-1},
		{atCoords.first-(1*dir), atCoords.second+1},
	};

	for (std::pair<int, int> coords : takesToCheck)
	{
		if (areCoordinatesValid(coords))
		{
			Piece* pieceToBeTaken = getPiece(coords);
			if (pieceToBeTaken != nullptr)
			{
				if (pieceToBeTaken->getColor() != pieceAtCoords->getColor())
				{
					auto taken = setPiece(coords, setPiece(atCoords, nullptr));
					//if (isCheck(pieceAtCoords->getColor()))
					if (true) // TODO... check for check in here
					{
						setPiece(atCoords, setPiece(coords, std::move(taken)));
					}
					else
					{
						validMoves.push_back(coords);
					}
				}
			}
		}
	}

	if (areCoordinatesValid({ atCoords.first - (1 * dir), atCoords.second }))
	{
		Piece* pieceInFront = getPiece({ atCoords.first - (1 * dir), atCoords.second });
		if (pieceInFront == nullptr)
		{
			validMoves.push_back({ atCoords.first - (1 * dir), atCoords.second });
			if (!pieceAtCoords->hasMadeFirstMove() && areCoordinatesValid({ atCoords.first - (2 * dir), atCoords.second }))
			{
				Piece* twoInFront = getPiece({ atCoords.first - (2 * dir), atCoords.second });
				if (twoInFront == nullptr)
				{
					validMoves.push_back({ atCoords.first - (2 * dir), atCoords.second });
				}
			}
		}
	}

	return validMoves;
}

void Board::move(std::pair<int, int> from, std::pair<int, int> to)
{
	if (this->getPiece(from)->isMoveValid(this, from, to))
	{
		setPiece(to, setPiece(from, nullptr));
	}
}

bool Board::areCoordinatesValid(std::pair<int, int> coordinates) const
{
	if (coordinates.first >= width || coordinates.first < 0)
		return false;

	if (coordinates.second >= height || coordinates.second < 0)
		return false;
	
	return true;
}
