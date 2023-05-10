#include "Board.h"

Board::Board(int width, int height)
{
	this->width = width;
	this->height = height;
	movesTracker = new MovesTracker(this);

	for (int j = 0; j < height; j++)
	{
		squares.push_back(std::vector<Square>());
		for (int i = 0; i < width; i++)
		{
			squares[j].push_back(Square());
		}
	}
}

Board::~Board()
{
	delete movesTracker;
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
			auto taken = setPiece({ atCoords.first - (1 * dir), atCoords.second }, setPiece(atCoords, nullptr));
			if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
			{
				validMoves.push_back({ atCoords.first - (1 * dir), atCoords.second });
			}
			setPiece(atCoords, setPiece({ atCoords.first - (1 * dir), atCoords.second }, std::move(taken)));

			if (!pieceAtCoords->hasMadeFirstMove() && areCoordinatesValid({ atCoords.first - (2 * dir), atCoords.second }))
			{
				Piece* twoInFront = getPiece({ atCoords.first - (2 * dir), atCoords.second });
				if (twoInFront == nullptr)
				{
					auto taken = setPiece({ atCoords.first - (2 * dir), atCoords.second }, setPiece(atCoords, nullptr));
					if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
					{
						validMoves.push_back({ atCoords.first - (2 * dir), atCoords.second });
					}
					setPiece(atCoords, setPiece({ atCoords.first - (2 * dir), atCoords.second }, std::move(taken)));
				}
			}
		}
	}

	return validMoves;
}

std::vector<std::pair<int, int>> Board::getKingMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
	std::vector<std::pair<int, int>> validKingMoves;
	std::vector<std::pair<int, int>> movesToCheck = {
		{atCoords.first - 1, atCoords.second - 1},
		{atCoords.first - 1, atCoords.second},
		{atCoords.first - 1, atCoords.second + 1},
		{atCoords.first, atCoords.second - 1},
		{atCoords.first, atCoords.second + 1},
		{atCoords.first + 1, atCoords.second - 1},
		{atCoords.first + 1, atCoords.second},
		{atCoords.first + 1, atCoords.second + 1},
	};

	for (auto& move : movesToCheck)
		addMoveIfValid(atCoords, move, validKingMoves, ignoreCheck);

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
		addMoveIfValid(atCoords, move, validKnightMoves, ignoreCheck);
		//if (areCoordinatesValid(move))
		//{
		//	Piece* pieceToBeTaken = getPiece(move);
		//	if (pieceToBeTaken == nullptr || pieceToBeTaken->getColor() != knightAtCoords->getColor())
		//	{
		//		auto taken = setPiece(move, setPiece(atCoords, nullptr));
		//		if (ignoreCheck || !isCheck(knightAtCoords->getColor()))
		//		{
		//			validKnightMoves.push_back(move);
		//		}
		//		setPiece(atCoords, setPiece(move, std::move(taken)));
		//	}

		//}
	}

	return validKnightMoves;
}

std::vector<std::pair<int, int>> Board::getHorizontalMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
	//int row = atCoords.first;
	//int col = atCoords.second;
	//Piece* pieceAtCoords = squares[row][col].getPiece();

	//std::vector<std::pair<int, int>> validHorizontalMoves;

	//bool areSquaresLeft = true;
	//int dir = -1;
	//int checkCol = col;
	//while (areSquaresLeft)
	//{
	//	checkCol += dir;
	//	if (areCoordinatesValid({ row, checkCol }))
	//	{
	//		Piece* pieceAtSquare = squares[row][checkCol].getPiece();
	//		if (pieceAtSquare == nullptr)
	//		{
	//			auto taken = setPiece({ row, checkCol }, setPiece(atCoords, nullptr));
	//			if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
	//			{
	//				validHorizontalMoves.push_back({ row, checkCol });
	//			}
	//			setPiece(atCoords, setPiece({ row, checkCol }, std::move(taken)));
	//		}
	//		else if (pieceAtSquare->getColor() != pieceAtCoords->getColor())
	//		{
	//			auto taken = setPiece({ row, checkCol }, setPiece(atCoords, nullptr));
	//			if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
	//			{
	//				validHorizontalMoves.push_back({ row, checkCol });
	//			}
	//			setPiece(atCoords, setPiece({ row, checkCol }, std::move(taken)));
	//			checkCol = col;
	//			dir += 2;
	//		}
	//		else
	//		{
	//			checkCol = col;
	//			dir += 2;
	//		}

	//	}
	//	else
	//	{
	//		checkCol = col;
	//		dir += 2;
	//	}
	//	if (dir > 1)
	//	{
	//		areSquaresLeft = false;
	//	}
	//}

	int row = atCoords.first;
	int col = atCoords.second;
	Piece* pieceAtCoords = squares[row][col].getPiece();

	std::vector<std::pair<int, int>> validHorizontalMoves;

	int dir = -1;
	int checkCol = col;

	while (dir <= 1)
	{
		checkCol += dir;
		Board::moveState mvFeedback = addMoveIfValid(atCoords, { row, checkCol }, validHorizontalMoves, ignoreCheck);
		if (mvFeedback.status == Board::moveState::Status::invalid || mvFeedback.reason == Board::moveState::Reason::valid_takes_enemy)
		{
			dir += 2;
			checkCol = col;
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

	int dir = -1;
	int checkRow = row;

	while (dir <= 1)
	{
		checkRow += dir;
		Board::moveState mvFeedback = addMoveIfValid(atCoords, { checkRow, col }, validVerticalMoves, ignoreCheck);
		if (mvFeedback.status == Board::moveState::Status::invalid || mvFeedback.reason == Board::moveState::Reason::valid_takes_enemy)
		{
			dir += 2;
			checkRow = row;
		}
	}

	//while (areSquaresLeft)
	//{
	//	checkRow += dir;
	//	if (areCoordinatesValid({ checkRow, col }))
	//	{
	//		Piece* pieceAtSquare = squares[checkRow][col].getPiece();
	//		// Square is empty
	//		if (pieceAtSquare == nullptr)
	//		{
	//			auto taken = setPiece({ checkRow, col }, setPiece(atCoords, nullptr));
	//			if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
	//			{
	//				validVerticalMoves.push_back({ checkRow, col });
	//			}
	//			setPiece(atCoords, setPiece({ checkRow, col }, std::move(taken)));
	//		}
	//		// Square has enemy's piece
	//		else if (pieceAtSquare->getColor() != pieceAtCoords->getColor())
	//		{
	//			auto taken = setPiece({ checkRow, col }, setPiece(atCoords, nullptr));
	//			if (ignoreCheck || !isCheck(pieceAtCoords->getColor()))
	//			{
	//				validVerticalMoves.push_back({ checkRow, col });
	//			}
	//			setPiece(atCoords, setPiece({ checkRow, col }, std::move(taken)));
	//			checkRow = row;
	//			dir += 2;
	//		}
	//		// Square has your piece
	//		else
	//		{
	//			checkRow = row;
	//			dir += 2;
	//		}

	//	}
	//	// coords out of board
	//	else
	//	{
	//		checkRow = row;
	//		dir += 2;
	//	}
	//	if (dir > 1)
	//	{
	//		areSquaresLeft = false;
	//	}
	//}

	return validVerticalMoves;
}

std::vector<std::pair<int, int>> Board::getDiagonalMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
	int row = atCoords.first;
	int col = atCoords.second;
	Piece* pieceAtCoords = squares[row][col].getPiece();

	std::vector<std::pair<int, int>> validDiagonalMoves;

	int dir = -1;
	int checkRow = row;
	int checkColLeft = col;
	int checkColRight = col;
	bool leftInvalid = false;
	bool rightInvalid = false;

	while (dir <= 1)
	{
		checkRow += dir;
		checkColLeft += dir;
		checkColRight -= dir;

		if (!leftInvalid)
		{
			Board::moveState mvFeedbackLeft = addMoveIfValid(atCoords, { checkRow, checkColLeft }, validDiagonalMoves, ignoreCheck);
			leftInvalid = mvFeedbackLeft.status == Board::moveState::Status::invalid || mvFeedbackLeft.reason == Board::moveState::Reason::valid_takes_enemy;
		}
		if (!rightInvalid)
		{
			Board::moveState mvFeedbackRight = addMoveIfValid(atCoords, { checkRow, checkColRight }, validDiagonalMoves, ignoreCheck);
			rightInvalid = mvFeedbackRight.status == Board::moveState::Status::invalid || mvFeedbackRight.reason == Board::moveState::Reason::valid_takes_enemy;
		}

		if (leftInvalid && rightInvalid)
		{
			checkRow = row;
			checkColLeft = col;
			checkColRight = col;
			dir += 2;
			leftInvalid = false;
			rightInvalid = false;
		}
	}

	return validDiagonalMoves;
}


void Board::move(std::pair<int, int> from, std::pair<int, int> to)
{
	// moves found piece (doesn't check if move is valid)
	Piece* movedPiece = this->getPiece(from);
	Piece* takenPiece = this->getPiece(to);

	if (movedPiece)
	{
		bool tookPiece = this->getPiece(to) != nullptr;
		bool takenPieceMoved = takenPiece != nullptr && takenPiece->hasMadeFirstMove();

		MovesTracker::Move mv(
			movedPiece->getType(),
			takenPiece == nullptr ? Piece::Type::NONE : takenPiece->getType(), 
			movedPiece->getColor(), 
			from, 
			to, 
			takenPiece ? takenPiece->hasMadeFirstMove() : false
		);
		
		movesTracker->addMove(mv);

		this->getPiece(from)->handleGotMoved();
		setPiece(to, setPiece(from, nullptr));

		this->getPiece(to)->setMadeFirstMove(true);

		// If current moved checked enemy
		if (isCheck(getPiece(to)->otherColor()))
		{
			if (isCheckMate(getPiece(to)->otherColor()))
			{
				std::cout << "CHECK MATE!";
				throw std::runtime_error("CHECKMATE NOT HANDLED YET!");
			}
		}
		// If move stalemated anyone
		else if (isStalemate(Piece::Color::Black) || isStalemate(Piece::Color::White))
		{
			throw std::domain_error("BRUH :((");
		}
	}
}

bool Board::isCheck(Piece::Color const piecesColor)
{
	auto kingCoords = getKingLocation(piecesColor);
	Piece* king = getPiece(kingCoords);

	auto knightChecks = getKnightMoves(kingCoords, true);
	auto rookChecksVer = getVerticalMoves(kingCoords, true);
	auto rookChecksHor = getHorizontalMoves(kingCoords, true);
	auto bishopChecks = getDiagonalMoves(kingCoords, true);
	auto kingMoves = getKingMoves(kingCoords, true);

	std::vector<std::pair<int, int>> rookChecks;
	rookChecks.insert(rookChecks.end(), rookChecksVer.begin(), rookChecksVer.end());
	rookChecks.insert(rookChecks.end(), rookChecksHor.begin(), rookChecksHor.end());

	for (auto& move : knightChecks)
	{
		if ( Knight* p = dynamic_cast<Knight*>(getPiece(move)) )
			return true;
	}

	for (auto& move : rookChecks)
	{
		Queen* q = dynamic_cast<Queen*>(getPiece(move));
		Rook* r = dynamic_cast<Rook*>(getPiece(move));
		if (q || r)
			return true;
	}

	for (auto& move : bishopChecks)
	{
		Bishop* b = dynamic_cast<Bishop*>(getPiece(move));
		Queen* q = dynamic_cast<Queen*>(getPiece(move));
		if (b || q)
			return true;

		// checked by pawn
		Pawn* p = dynamic_cast<Pawn*>(getPiece(move));
		int dir = piecesColor == Piece::Color::White ? 1 : -1;
		if ((move.first - kingCoords.first) * dir == 1 && p)
			return true;
	}

	for (auto& move : kingMoves)
	{
		if (King* k = dynamic_cast<King*>(getPiece(move)))
			return true;
	}

	return false;
}

bool Board::isCheckMate(Piece::Color const piecesColor)
{
	for (int row = 0; row < squares.size(); row++)
	{
		for (int col = 0; col < squares[row].size(); col++)
		{
			Square& sqr = squares[row][col];
			Piece* piece = sqr.getPiece();
			if (piece != nullptr && piece->getColor() == piecesColor)
			{
				auto validMoves = piece->getValidMoves(this, { row, col });
				if (validMoves.size() > 0)
					return false;
			}
		}
	}
	return true;
}

bool Board::isStalemate(Piece::Color const piecesColor)
{
	for (int row = 0; row < squares.size(); row++)
	{
		for (int col = 0; col < squares[row].size(); col++)
		{
			Square& sqr = squares[row][col];
			Piece* piece = sqr.getPiece();

			if (piece != nullptr && piece->getColor() == piecesColor && piece->getValidMoves(this, { row, col }).size() != 0)
				return false;
		}
	}
	return true;
}

bool Board::areCoordinatesValid(std::pair<int, int> coordinates) const
{
	if (coordinates.first >= width || coordinates.first < 0)
		return false;

	if (coordinates.second >= height || coordinates.second < 0)
		return false;
	
	return true;
}

MovesTracker* Board::getMovesTracker() const
{
	return movesTracker;
}

Piece::Color Board::getTurn() const
{
	return turn;
}

void Board::setTurn(Piece::Color const turnColor)
{
	turn = turnColor;
}

Board::moveState Board::addMoveIfValid(std::pair<int, int>& from, std::pair<int, int> to, std::vector<std::pair<int, int>>& addTo, bool ignoreCheck)
{
	moveState feedback = moveState();
	
	Piece* movedPiece = getPiece(from);

	if (!areCoordinatesValid(to))
	{
		feedback.status = Board::moveState::Status::invalid;
		feedback.reason = Board::moveState::Reason::invalid_wrong_coords;
		return feedback;
	}

	Piece* pieceMovedTo = squares[to.first][to.second].getPiece();
	if (pieceMovedTo == nullptr || pieceMovedTo->getColor() != movedPiece->getColor())
	{
		auto taken = setPiece(to, setPiece(from, nullptr));
		if (ignoreCheck || !isCheck(movedPiece->getColor()))
		{
			feedback.status = Board::moveState::Status::valid;
			feedback.reason = pieceMovedTo == nullptr ? Board::moveState::Reason::valid_empty : Board::moveState::Reason::valid_takes_enemy;
			addTo.push_back(to);
		}
		// else (if is check)
		else
		{
			feedback.status = Board::moveState::Status::invalid;
			feedback.reason = Board::moveState::Reason::invalid_causes_own_check;
		}
		setPiece(from, setPiece(to, std::move(taken)));
		return feedback;
	}

	// If would take own piece
	feedback.status = Board::moveState::Status::invalid;
	feedback.reason = Board::moveState::Reason::invalid_takes_own;
	return feedback;
}