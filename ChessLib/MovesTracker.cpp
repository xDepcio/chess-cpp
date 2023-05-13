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

MovesTracker::Move MovesTracker::getPointedMove() const
{
	return moves[pointedMoveNum];
}

int MovesTracker::getPointedMoveIndex() const
{
	return pointedMoveNum;
}

bool MovesTracker::onLatestMove() const
{
	return pointedMoveNum == moves.size() - 1;
}

void MovesTracker::addMove(Move const& move)
{
	moves.push_back(move);
	pointedMoveNum = moves.size() - 1;
}

void MovesTracker::next()
{
	pointedMoveNum++;
	Move moveToMake = moves[pointedMoveNum];
	makeMove(moveToMake);
}

void MovesTracker::makeMove(Move const& move)
{
	if (move.enPassant != Pawn::EnPassant::NONE)
	{
		std::pair<int, int> takenPawnCoords = { move.pieceColor == Piece::Color::White ? move.to.first + 1 : move.to.first - 1, move.to.second };
		trackedBoard->setPiece(move.to, trackedBoard->setPiece(move.from, nullptr));
		trackedBoard->setPiece(takenPawnCoords, nullptr);
	}
	else if (move.castle != King::Castle::NONE)
	{
		std::pair<int, int> rookCoords = { move.from.first, move.to.second == 2 ? 0 : 7 };
		int dirSign = Helpers::sgn<int>(move.from.second - rookCoords.second);

		std::pair<int, int> newKingCoords = {
			move.from.first,
			move.from.second - 2 * dirSign
		};

		std::pair<int, int> newRookCoords = {
			move.from.first,
			newKingCoords.second + dirSign
		};

		trackedBoard->setPiece(move.to, trackedBoard->setPiece(move.from, nullptr));
		trackedBoard->setPiece(newRookCoords, trackedBoard->setPiece(rookCoords, nullptr));
	}
	else
	{
		trackedBoard->setPiece(move.to, trackedBoard->setPiece(move.from, nullptr));
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
		auto move = moves[i];
		if (move.castle == King::Castle::NONE)
		{
			result << coordsToString(move.to) << " ";
		}
	}

	return result.str();
}

void MovesTracker::previous()
{
	Move moveToRevert = moves[pointedMoveNum];
	revertMove(moveToRevert);
	pointedMoveNum--;
}

void MovesTracker::revertMove(Move const& move)
{
	if (move.enPassant != Pawn::EnPassant::NONE)
	{
		trackedBoard->setPiece(move.from, trackedBoard->setPiece(move.to, nullptr));
		
		trackedBoard->setPiece(
			{ move.pieceColor == Piece::Color::White ? move.to.first + 1 : move.to.first - 1, move.to.second },
			makePieceFromType(Piece::Type::PAWN, Helpers::getOtherColor(move.pieceColor))
		);
	}
	else if (move.castle != King::Castle::NONE)
	{
		trackedBoard->setPiece(move.from, makePieceFromType(move.pieceType, move.pieceColor));
		trackedBoard->setPiece(move.to, nullptr);

		std::pair<int, int> rookCurrCoords = { move.from.first, move.castle == King::Castle::LONG ? 3 : 5};
		std::pair<int, int> rookPrevCoords = { move.from.first, move.castle == King::Castle::LONG ? 0 : 7};
		trackedBoard->setPiece(rookPrevCoords, makePieceFromType(Piece::Type::ROOK, move.pieceColor));
		trackedBoard->setPiece(rookCurrCoords, nullptr);
	}
	else
	{
		trackedBoard->setPiece(move.from, makePieceFromType(move.pieceType, move.pieceColor));
		trackedBoard->setPiece(move.to, makePieceFromType(move.takenPiece, Helpers::getOtherColor(move.pieceColor)));
	}
}

std::unique_ptr<Piece> MovesTracker::makePieceFromType(Piece::Type type, Piece::Color color)
{
	switch (type)
	{
	case Piece::Type::BISHOP:
		return std::make_unique<Bishop>(color);
	case Piece::Type::PAWN:
		return std::make_unique<Pawn>(color);
	case Piece::Type::ROOK:
		return std::make_unique<Rook>(color);
	case Piece::Type::QUEEN:
		return std::make_unique<Queen>(color);
	case Piece::Type::KNIGHT:
		return std::make_unique<Knight>(color);
	case Piece::Type::KING:
		return std::make_unique<King>(color);
	case Piece::Type::NONE:
		return nullptr;
	default:
		throw std::runtime_error(":()()");
		break;
	}
}

std::string MovesTracker::coordsToString(std::pair<int, int> const& coords) const
{
	std::ostringstream oss;
	std::vector<char> cols = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	oss << cols[coords.second] << 8 - coords.first;
	return oss.str();
}
