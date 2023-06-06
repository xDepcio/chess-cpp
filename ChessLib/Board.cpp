#include <sstream>
#include <unordered_map>
#include "Board.h"
#include "MovesTracker.h"
#include "Queen.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "Square.h"

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
			squares[j].push_back(Square({j, i}));
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

std::string Board::getFenBoard()
{
	std::stringstream fen;
	std::stringstream castle;
	int empty = 0;
	for (int i = 0; i < squares.size(); i++)
	{
		
		empty = 0;
		for (int j = 0; j < squares[0].size(); j++)
		{
			
			Piece* squarePiece = squares[i][j].getPiece();
			if (squarePiece != nullptr)
			{
				if (empty != 0)
				{
					fen << empty;
					empty = 0;
				}
				fen << squarePiece->getName()[1];
			}
			else
			{
				empty += 1;
			}
			
		}
		if (empty == 8 or empty != 0)
		{
			fen << empty;
		}
		if(i != squares.size() - 1)
			fen << "/";
	}
	
	fen << " " << (getTurn() == Color::White ? "w" : "b") << " ";

	size_t castle_moves_w = getCastleMoves(Color::White).size();
	size_t castle_moves_b = getCastleMoves(Color::Black).size();

	switch (castle_moves_w)
	{
	case 1:
		castle << "K";
		break;
	case 2:
		castle << "KQ";
		break;
	default:
		break;
	}
	switch (castle_moves_b)
	{
	case 1:
		castle << "k";
		break;
	case 2:
		castle << "kq";
		break;
	default:
		break;
	}

	if (castle.str().length() == 0) castle << "- ";
	

	fen << castle.str();
	fen << "- 0 ";
	fen << (movesTracker->getMoveCount()+2)/2;

	fen << std::endl;

	return fen.str();
	
}

void Board::setFenBoard(std::string fenPos)
{
	//for (int i = 0; i < squares.size(); i++)
	//{
	//	for (int j = 0; j < squares[0].size(); j++)
	//	{
	//		int poi* squares.size() + j
	//	}
	//}
	std::unordered_map<char, int> PieceLet{ {'p', 0}, {'r', 1}, {'n', 2}, {'b', 3}, {'k', 4}, {'q', 5} };
	int pos_num = 0;
	//int pieceIdBlack = 201;
	//int pieceIdWhite = 101;
	for (auto character : fenPos)
	{
		//int pieceId;
		//std::cout << getFenBoard() << std::endl;
		int iPos = pos_num / squares.size();
		int jPos = pos_num - iPos * squares.size();

		Color pieceColor;

		if (character == ' ')
			return;

		if (character == '/')
			continue;

		else if (isalpha(character))
		{
			if (int(character) < 97)
			{
				pieceColor = Color::White;
				//pieceId = pieceIdWhite;
				//pieceIdWhite++;
			}
			else
			{
				pieceColor = Color::Black;
				//pieceId = pieceIdBlack;
				//pieceIdBlack++;
			}

			character = tolower(character);

			switch (PieceLet[character])
			{
			case 0:
			{
				setPiece({ iPos, jPos }, std::make_unique<Pawn>(pieceColor));
				pos_num += 1;
				break;
			}
			case 1:
			{
				setPiece({ iPos, jPos }, std::make_unique<Rook>(pieceColor));
				pos_num += 1;
				break;
			}
			case 2:
			{
				setPiece({ iPos, jPos }, std::make_unique<Knight>(pieceColor));
				pos_num += 1;
				break;
			}
			case 3:
			{
				setPiece({ iPos, jPos }, std::make_unique<Bishop>(pieceColor));
				pos_num += 1;
				break;
			}
			case 4:
			{
				setPiece({ iPos, jPos }, std::make_unique<King>(pieceColor));
				pos_num += 1;
				break;
			}
			case 5:
			{
				setPiece({ iPos, jPos }, std::make_unique<Queen>(pieceColor));
				pos_num += 1;
				break;
			}
			}
			//setPiece({ 1, 0 }, std::make_unique<Pawn>(Color::Black, 201));


		}
		else
			pos_num += atoi(&character);
	}
	
	




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

std::unique_ptr<Piece> Board::getPieceUniquePtr(const std::pair<int, int>& pieceCoords)
{
	return squares[pieceCoords.first][pieceCoords.second].getPieceUniquePtr();
}

std::pair<int, int> Board::getKingLocation(Color const kingColor) const
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
	int dir = pieceAtCoords->getColor() == Color::White ? 1 : -1;

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
	}

	return validKnightMoves;
}

std::vector<std::pair<int, int>> Board::getHorizontalMoves(std::pair<int, int> atCoords, bool ignoreCheck)
{
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
		if (mvFeedback.reason == Board::moveState::Reason::invalid_wrong_coords || mvFeedback.reason == Board::moveState::Reason::invalid_takes_own || mvFeedback.reason == Board::moveState::Reason::valid_takes_enemy)
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
		if (mvFeedback.reason == Board::moveState::Reason::invalid_wrong_coords || mvFeedback.reason == Board::moveState::Reason::invalid_takes_own || mvFeedback.reason == Board::moveState::Reason::valid_takes_enemy)
		{
			dir += 2;
			checkRow = row;
		}
	}

	return validVerticalMoves;
}

std::vector<std::pair<int, int>> Board::getCastleMoves(Color kingColor)
{
	auto kingCoords = getKingLocation(kingColor);
	Piece* king = getPiece(kingCoords);
	std::vector<std::pair<int, int>> moves = {};

	if (king->hasMadeFirstMove() || isCheck(kingColor))
		return moves;

	if (getPiece({ kingCoords.first, 0 }) && !getPiece({ kingCoords.first, 0 })->hasMadeFirstMove())
	{
		if (!getPiece({ kingCoords.first, 3 }) && !getPiece({ kingCoords.first, 2 }) && !getPiece({ kingCoords.first, 1 }))
		{
			setPiece({ kingCoords.first, 3 }, setPiece(kingCoords, nullptr));
			if (!isCheck(kingColor))
			{
				setPiece(kingCoords, setPiece({ kingCoords.first, 3 }, nullptr));
				addMoveIfValid(kingCoords, { kingCoords.first, 2 }, moves);
			}
			else
			{
				setPiece(kingCoords, setPiece({ kingCoords.first, 3 }, nullptr));
			}
		}
	}

	if (getPiece({ kingCoords.first, 7 }) && !getPiece({ kingCoords.first, 7 })->hasMadeFirstMove())
	{
		if (!getPiece({ kingCoords.first, 5 }) && !getPiece({ kingCoords.first, 6 }))
		{
			setPiece({ kingCoords.first, 5 }, setPiece(kingCoords, nullptr));
			if (!isCheck(kingColor))
			{
				setPiece(kingCoords, setPiece({ kingCoords.first, 5 }, nullptr));
				addMoveIfValid(kingCoords, { kingCoords.first, 6 }, moves);
			}
			else
			{
				setPiece(kingCoords, setPiece({ kingCoords.first, 5 }, nullptr));
			}
		}
	}

	return moves;
}

std::vector<std::pair<int, int>> Board::getEnPassantMoves(std::pair<int, int> pawnCoords)
{
	Pawn* pawn = dynamic_cast<Pawn*>(getPiece(pawnCoords));
	if (!pawn)
		return {};

	std::vector<std::pair<int, int>> validMoves;
	if (pawn->canEnPassantLeft())
	{
		validMoves.push_back(
			{
				pawn->getColor() == Color::White ? pawnCoords.first - 1 : pawnCoords.first + 1,
				pawnCoords.second - 1
			}
		);
	}
	if (pawn->canEnPassantRight())
	{
		validMoves.push_back(
			{
				pawn->getColor() == Color::White ? pawnCoords.first - 1 : pawnCoords.first + 1,
				pawnCoords.second + 1
			}
		);
	}

	return validMoves;
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
			leftInvalid = mvFeedbackLeft.reason == Board::moveState::Reason::invalid_wrong_coords || mvFeedbackLeft.reason == Board::moveState::Reason::invalid_takes_own || mvFeedbackLeft.reason == Board::moveState::Reason::valid_takes_enemy;
		}
		if (!rightInvalid)
		{
			Board::moveState mvFeedbackRight = addMoveIfValid(atCoords, { checkRow, checkColRight }, validDiagonalMoves, ignoreCheck);
			rightInvalid = mvFeedbackRight.reason == Board::moveState::Reason::invalid_wrong_coords || mvFeedbackRight.reason == Board::moveState::Reason::invalid_takes_own || mvFeedbackRight.reason == Board::moveState::Reason::valid_takes_enemy;
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
	invalidateEnPassantes(movedPiece->getColor());

	if (movedPiece)
	{
		bool tookPiece = this->getPiece(to) != nullptr;
		bool takenPieceMoved = takenPiece != nullptr && takenPiece->hasMadeFirstMove();

		auto mvPtr = std::make_unique<MovesTracker::Move>(
			movedPiece->getType(),
			takenPiece == nullptr ? PieceType::NONE : takenPiece->getType(),
			getPieceUniquePtr(to),
			movedPiece->getColor(),
			from, 
			to, 
			takenPiece ? takenPiece->hasMadeFirstMove() : false,
			Castle::NONE,
			std::vector<std::pair<int, int>>({from, to}),
			EnPassant::NONE,
			isCheck(movedPiece->otherColor())
		);

		movesTracker->addMove(std::move(mvPtr));

		this->getPiece(from)->handleGotMoved();
		setPiece(to, setPiece(from, nullptr));

		this->getPiece(to)->setMadeFirstMove(true);

		// If current moved checked enemy
		if (isCheck(getPiece(to)->otherColor()))
		{
			if (isCheckMate(getPiece(to)->otherColor()))
			{
				setBoardState(movedPiece->getColor() == Color::White ? BoardState::CHECKMATED_BLACK : BoardState::CHECKMATED_WHITE);
			}
		}
		// If move stalemated anyone
		else if (isStalemate(Color::Black) || isStalemate(Color::White))
		{
			setBoardState(BoardState::STALEMATE);
		}
		// invalidate previously avalible enpassantes
		//if (shouldInvalidateEnPassantes)
		//{
		//	invalidateEnPassantes(movedPiece->getColor());
		//}
	}
}

bool Board::isCheck(Color const piecesColor)
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
		int dir = piecesColor == Color::White ? -1 : 1;
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

bool Board::isCheckMate(Color const piecesColor)
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

bool Board::isStalemate(Color const piecesColor)
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

Color Board::getTurn() const
{
	return turn;
}

void Board::setTurn(Color const turnColor)
{
	turn = turnColor;
}

void Board::invalidateEnPassantesOnNextMove()
{
	shouldInvalidateEnPassantes = true;
}

void Board::setBoardState(BoardState stateToSet)
{
	boardState = stateToSet;
}

BoardState Board::getBoardState() const
{
	return boardState;
}

void Board::requestPromotionChoice(std::pair<int, int> const& moveFrom, std::pair<int, int> const& moveTo)
{
	setBoardState(BoardState::REQUEST_PROMOTION);
	promoMoveFrom = moveFrom;
	promoMoveTo = moveTo;

}

void Board::receivePromotionChoice(Promotions promotion)
{
	auto movedPawn = getPiece(promoMoveFrom);
	auto takenPiece = getPiece(promoMoveTo);
	auto movedPawnColor = movedPawn->getColor();

	auto mvPtr = std::make_unique<MovesTracker::Move>(
		PieceType::PAWN,
		takenPiece == nullptr ? PieceType::NONE : takenPiece->getType(),
		getPieceUniquePtr(promoMoveTo),
		movedPawn->getColor(),
		promoMoveFrom,
		promoMoveTo,
		takenPiece ? takenPiece->hasMadeFirstMove() : false,
		Castle::NONE,
		std::vector<std::pair<int, int>>({ promoMoveFrom, promoMoveTo }),
		EnPassant::NONE,
		false,
		promotion,
		getPieceUniquePtr(promoMoveFrom)
	);


	switch (promotion)
	{
	case Promotions::ROOK:
		setPiece(promoMoveTo, std::make_unique<Rook>(movedPawnColor));
		break;
	case Promotions::QUEEN:
		setPiece(promoMoveTo, std::make_unique<Queen>(movedPawnColor));
		break;
	case Promotions::KNGIHT:
		setPiece(promoMoveTo, std::make_unique<Knight>(movedPawnColor));
		break;
	case Promotions::BISHOP:
		setPiece(promoMoveTo, std::make_unique<Bishop>(movedPawnColor));
		break;
	case Promotions::NONE:
		break;
	default:
		break;
	}

	movesTracker->addMove(std::move(mvPtr));
}

Board::moveState Board::addMoveIfValid(std::pair<int, int> from, std::pair<int, int> to, std::vector<std::pair<int, int>>& addTo, bool ignoreCheck)
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

void Board::invalidateEnPassantes(Color piecesColorToInvalidate)
{
	for (auto& row : squares)
	{
		for (auto& sqr : row)
		{
			Pawn* p = dynamic_cast<Pawn*>(sqr.getPiece());
			if (p && p->getColor() == piecesColorToInvalidate)
			{
				p->setValidEnPassantLeft(false);
				p->setValidEnPassantRight(false);
			}
		}
	}
}
