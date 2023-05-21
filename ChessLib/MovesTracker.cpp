#include "MovesTracker.h"
#include "Board.h"
#include "Helpers.h"
#include <sstream>
#include "Queen.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

MovesTracker::Move* MovesTracker::getPointedMove() const
{
	return moves[pointedMoveNum].get();
}

int MovesTracker::getPointedMoveIndex() const
{
	return pointedMoveNum;
}

bool MovesTracker::onLatestMove() const
{
	return pointedMoveNum == moves.size() - 1;
}

void MovesTracker::addMove(std::unique_ptr<Move> movePtr)
{
	moves.push_back(std::move(movePtr));
	pointedMoveNum = moves.size() - 1;
}

void MovesTracker::next()
{
	pointedMoveNum++;
	Move* moveToMake = moves[pointedMoveNum].get();
	makeMove(moveToMake);
}

void MovesTracker::makeMove(Move* move)
{
	if (move->promotion != Promotions::NONE)
	{
		move->promotedPawn = std::move(trackedBoard->getPieceUniquePtr(move->from));
		switch (move->promotion)
		{
		case Promotions::ROOK:
			trackedBoard->setPiece(move->to, std::make_unique<Rook>(move->pieceColor));
			break;
		case Promotions::KNGIHT:
			trackedBoard->setPiece(move->to, std::make_unique<Knight>(move->pieceColor));
			break;
		case Promotions::BISHOP:
			trackedBoard->setPiece(move->to, std::make_unique<Bishop>(move->pieceColor));
			break;
		case Promotions::QUEEN:
			trackedBoard->setPiece(move->to, std::make_unique<Queen>(move->pieceColor));
			break;
		default:
			break;
		}
	}
	else if (move->enPassant != EnPassant::NONE)
	{
		std::pair<int, int> takenPawnCoords = { move->pieceColor == Color::White ? move->to.first + 1 : move->to.first - 1, move->to.second };
		move->takenPiecePtr = std::move(trackedBoard->getPieceUniquePtr(takenPawnCoords));
		trackedBoard->setPiece(move->to, trackedBoard->setPiece(move->from, nullptr));
		trackedBoard->setPiece(takenPawnCoords, nullptr);
	}
	else if (move->castle != Castle::NONE)
	{
		std::pair<int, int> rookCoords = { move->from.first, move->to.second == 2 ? 0 : 7 };
		int dirSign = Helpers::sgn<int>(move->from.second - rookCoords.second);

		std::pair<int, int> newKingCoords = {
			move->from.first,
			move->from.second - 2 * dirSign
		};

		std::pair<int, int> newRookCoords = {
			move->from.first,
			newKingCoords.second + dirSign
		};

		trackedBoard->setPiece(move->to, trackedBoard->setPiece(move->from, nullptr));
		trackedBoard->setPiece(newRookCoords, trackedBoard->setPiece(rookCoords, nullptr));
	}
	else
	{
		move->takenPiecePtr = std::move(trackedBoard->getPieceUniquePtr(move->to));
		trackedBoard->setPiece(move->to, trackedBoard->setPiece(move->from, nullptr));
	}
}

void MovesTracker::updateToLatest()
{
	while (pointedMoveNum < moves.size())
	{
		next();
	}
}

std::string MovesTracker::toPgn() const
{
	// TODO... not finished
	std::ostringstream result;
	for (int i = 0; i < moves.size(); i++)
	{
		if (i % 2 == 0)
			result << i/2 + 1 << ". ";
		auto move = moves[i].get();
		if (move->castle == Castle::NONE && move->takenPiece == PieceType::NONE)
		{
			result << coordsToString(move->to) << " ";
		}
	}

	return result.str();
}

void MovesTracker::previous()
{
	Move* moveToRevert = moves[pointedMoveNum].get();
	revertMove(moveToRevert);
	pointedMoveNum--;
}

void MovesTracker::revertMove(Move* move)
{
	if (move->promotion != Promotions::NONE)
	{
		trackedBoard->setPiece(move->from, std::move(move->promotedPawn));
		trackedBoard->setPiece(move->to, std::move(move->takenPiecePtr));
	}
	else if (move->enPassant != EnPassant::NONE)
	{
		trackedBoard->setPiece(move->from, trackedBoard->setPiece(move->to, nullptr));
		
		trackedBoard->setPiece(
			{ move->pieceColor == Color::White ? move->to.first + 1 : move->to.first - 1, move->to.second },
			std::move(move->takenPiecePtr)
		);
	}
	else if (move->castle != Castle::NONE)
	{
		// Revert king move
		trackedBoard->setPiece(move->from, trackedBoard->setPiece(move->to, nullptr));

		// Revert rook move
		std::pair<int, int> rookCurrCoords = { move->from.first, move->castle == Castle::LONG ? 3 : 5};
		std::pair<int, int> rookPrevCoords = { move->from.first, move->castle == Castle::LONG ? 0 : 7};
		trackedBoard->setPiece(rookPrevCoords, trackedBoard->setPiece(rookCurrCoords, nullptr));
	}
	else
	{
		trackedBoard->setPiece(move->from, trackedBoard->setPiece(move->to, nullptr));
		trackedBoard->setPiece(move->to, std::move(move->takenPiecePtr));
	}
}

std::string MovesTracker::coordsToString(std::pair<int, int> const& coords) const
{
	std::ostringstream oss;
	std::vector<char> cols = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	oss << cols[coords.second] << 8 - coords.first;
	return oss.str();
}
