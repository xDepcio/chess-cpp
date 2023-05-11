#include "MovesTracker.h"
#include "Board.h"
#include "Helpers.h"

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
	trackedBoard->setPiece(move.to, trackedBoard->setPiece(move.from, nullptr));
}

void MovesTracker::updateToLatest()
{
	while (pointedMoveNum < moves.size())
	{
		next();
	}
}

void MovesTracker::previous()
{
	Move moveToRevert = moves[pointedMoveNum];
	revertMove(moveToRevert);
	pointedMoveNum--;
}

void MovesTracker::revertMove(Move const& move)
{
	//if (move.castle != King::Castle::NONE)
	//{
	//	trackedBoard->setPiece(move.from, makePieceFromType(move.pieceType, move.pieceColor));
	//	trackedBoard->setPiece(move.to, nullptr);

	//	std::pair<int, int> rookCurrCoords = { move.from.first, move.castle == King::Castle::LONG ? 3 : 5};
	//	std::pair<int, int> rookPrevCoords = { move.from.first, move.castle == King::Castle::LONG ? 0 : 7};
	//	trackedBoard->setPiece(rookPrevCoords, makePieceFromType(Piece::Type::ROOK, move.pieceColor));
	//	trackedBoard->setPiece(rookCurrCoords, nullptr);
	//}
	//else
	//{
		trackedBoard->setPiece(move.from, makePieceFromType(move.pieceType, move.pieceColor));
		trackedBoard->setPiece(move.to, makePieceFromType(move.takenPiece, Helpers::getOtherColor(move.pieceColor)));
	//}
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
	//case Piece::Type::KING:
		//return std::make_unique<King>(color);
	case Piece::Type::NONE:
		return nullptr;
	default:
		throw std::runtime_error(":()()");
		break;
	}
}