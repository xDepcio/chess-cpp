#include "Knight.h"
#include "MovesTracker.h"
#include "Board.h"

Knight::Knight(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = withColor == Piece::Color::Black ? "n" : "N";
	type = Type::KNIGHT;
}

Knight::Knight(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = withColor == Piece::Color::Black ? "n" : "N";
	type = Type::KNIGHT;
}

std::vector<std::pair<int, int>> Knight::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	if (!board->getMovesTracker()->onLatestMove())
		return {};
	return board->getKnightMoves(atCoords, ignoreCheck);
}
