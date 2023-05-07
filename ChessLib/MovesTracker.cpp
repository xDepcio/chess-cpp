#include "MovesTracker.h"
#include "Board.h"

MovesTracker::Move MovesTracker::getPointedMove() const
{
	return moves[pointedMoveNum];
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
	trackedBoard->setPiece(move.to, trackedBoard->setPiece(move.from, nullptr));
}

void MovesTracker::previous()
{
	Move moveToRevert = moves[pointedMoveNum];
	revertMove(moveToRevert);
	pointedMoveNum--;
}

void MovesTracker::revertMove(Move const& move)
{
	trackedBoard->setPiece(move.from, makePieceFromType(move.pieceType, move.pieceColor));
	trackedBoard->setPiece(move.to, makePieceFromType(move.takenPiece, move.pieceColor));
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
	case Piece::Type::NONE:
		return nullptr;
	default:
		throw std::runtime_error(":()()");
		break;
	}
}
