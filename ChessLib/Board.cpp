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
		std::cout << " " << 8 - i << " ";
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
	std::cout << "    a   b   c   d   e   f   g   h\n";
}

Piece* Board::getPiece(std::pair<int, int> coords) const
{
	return squares[coords.first][coords.second].getPiece();
}

std::pair<int, int> Board::getKingLocation(Piece::Color const kingColor) const
{
	int rowNum = 0;
	for (auto& row : squares)
	{
		int colNum = 0;
		for (auto& sqr : row)
		{
			King* sqrPiece = dynamic_cast<King*>(sqr.getPiece());
			if (sqrPiece != nullptr && sqrPiece->getColor() == kingColor)
			{
				return {rowNum, colNum};
			}

			colNum++;
		}
		
		rowNum++;
	}
	return {-1, -1};
}


std::vector<std::pair<int, int>> Board::getPawnMoves(std::pair<int, int> atCoords, bool ignoreCheck)
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
					if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
					{
						validMoves.push_back(coords);
					}
					setPiece(atCoords, setPiece(coords, std::move(taken)));
				}
			}
		}
	}

	if (areCoordinatesValid({ atCoords.first - (1 * dir), atCoords.second }))
	{
		Piece* pieceInFront = getPiece({ atCoords.first - (1 * dir), atCoords.second });
		if (pieceInFront == nullptr)
		{
			if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
			{
				validMoves.push_back({ atCoords.first - (1 * dir), atCoords.second });
			}

			if (!pieceAtCoords->hasMadeFirstMove() && areCoordinatesValid({ atCoords.first - (2 * dir), atCoords.second }))
			{
				Piece* twoInFront = getPiece({ atCoords.first - (2 * dir), atCoords.second });
				if (twoInFront == nullptr)
				{
					if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
					{
						validMoves.push_back({ atCoords.first - (2 * dir), atCoords.second });
					}
				}
			}
		}
	}

	return validMoves;
}

std::vector<std::pair<int, int>> Board::getKingMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
	std::vector<std::pair<int, int>> validKingMoves = {};
	return validKingMoves;
}

std::vector<std::pair<int, int>> Board::getKnightMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
	int row = atCoords.first;
	int col = atCoords.second;
	Piece* knightAtCoords = squares[row][col].getPiece();

	std::vector<std::pair<int, int>> validKnightMoves;

	std::vector<std::pair<int, int>> movesToCheck = {
		{row + 2, col - 1},
		{row + 2, col + 1},
		{row - 2, col - 1},
		{row - 2, col + 1},
		{row - 1, col - 2},
		{row + 1, col - 2},
		{row - 1, col + 2},
		{row + 1, col + 2},
	};

	for (auto& move : movesToCheck)
	{
		if (areCoordinatesValid(move))
		{
			Piece* pieceToBeTaken = getPiece(move);
			if (pieceToBeTaken == nullptr || pieceToBeTaken->getColor() != knightAtCoords->getColor())
			{
				auto taken = setPiece(move, setPiece(atCoords, nullptr));
				if (ignoreCheck || !isCheck(knightAtCoords->getColor()))
				{
					validKnightMoves.push_back(move);
				}
				setPiece(atCoords, setPiece(move, std::move(taken)));
			}

		}
	}

	return validKnightMoves;
}

std::vector<std::pair<int, int>> Board::getHorizontalMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
	int row = atCoords.first;
	int col = atCoords.second;
	Piece* pieceAtCoords = squares[row][col].getPiece();

	std::vector<std::pair<int, int>> validHorizontalMoves;

	bool areSquaresLeft = true;
	int dir = -1;
	int checkCol = col;
	while (areSquaresLeft)
	{
		checkCol += dir;
		if (areCoordinatesValid({ row, checkCol }))
		{
			Piece* pieceAtSquare = squares[row][checkCol].getPiece();
			if (pieceAtSquare == nullptr)
			{
				auto taken = setPiece({ row, checkCol }, setPiece(atCoords, nullptr));
				if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
				{
					validHorizontalMoves.push_back({ row, checkCol });
				}
				setPiece(atCoords, setPiece({ row, checkCol }, std::move(taken)));
			}
			else if (pieceAtSquare->getColor() != pieceAtCoords->getColor())
			{
				auto taken = setPiece({ row, checkCol }, setPiece(atCoords, nullptr));
				if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
				{
					validHorizontalMoves.push_back({ row, checkCol });
				}
				setPiece(atCoords, setPiece({ row, checkCol }, std::move(taken)));
				checkCol = col;
				dir += 2;
			}
			else
			{
				checkCol = col;
				dir += 2;
			}

		}
		else
		{
			checkCol = col;
			dir += 2;
		}
		if (dir > 1)
		{
			areSquaresLeft = false;
		}
	}

	return validHorizontalMoves;
}

std::vector<std::pair<int, int>> Board::getVerticalMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
	int row = atCoords.first;
	int col = atCoords.second;
	Piece* pieceAtCoords = squares[row][col].getPiece();

	std::vector<std::pair<int, int>> validVerticalMoves;

	bool areSquaresLeft = true;
	int dir = -1;
	int checkRow = row;
	while (areSquaresLeft)
	{
		checkRow += dir;
		if (areCoordinatesValid({ checkRow, col }))
		{
			Piece* pieceAtSquare = squares[checkRow][col].getPiece();
			// Square is empty
			if (pieceAtSquare == nullptr)
			{
				auto taken = setPiece({ checkRow, col }, setPiece(atCoords, nullptr));
				if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
				{
					validVerticalMoves.push_back({ checkRow, col });
				}
				setPiece(atCoords, setPiece({ checkRow, col }, std::move(taken)));
			}
			// Square has enemy's piece
			else if (pieceAtSquare->getColor() != pieceAtCoords->getColor())
			{
				auto taken = setPiece({ checkRow, col }, setPiece(atCoords, nullptr));
				if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
				{
					validVerticalMoves.push_back({ checkRow, col });
				}
				setPiece(atCoords, setPiece({ checkRow, col }, std::move(taken)));
				checkRow = row;
				dir += 2;
			}
			// Square has your piece
			else
			{
				checkRow = row;
				dir += 2;
			}

		}
		// coords out of board
		else
		{
			checkRow = row;
			dir += 2;
		}
		if (dir > 1)
		{
			areSquaresLeft = false;
		}
	}

	return validVerticalMoves;
}


void Board::move(std::pair<int, int> from, std::pair<int, int> to)
{
	if (this->getPiece(from)->isMoveValid(this, from, to))
	{
		this->getPiece(from)->handleGotMoved();
		setPiece(to, setPiece(from, nullptr));
	}
}

bool Board::isCheck(Piece::Color const piecesColor) const
{
	auto kingCoords = getKingLocation(piecesColor);
	return false;
}

bool Board::areCoordinatesValid(std::pair<int, int> coordinates) const
{
	if (coordinates.first >= width || coordinates.first < 0)
		return false;

	if (coordinates.second >= height || coordinates.second < 0)
		return false;
	
	return true;
}
