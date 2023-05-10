#include "Bishop.h"

Bishop::Bishop(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "b";
	Piece::type = Type::BISHOP;
}

Bishop::Bishop(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = "b";
	Piece::type = Type::BISHOP;
}

std::vector<std::pair<int, int>> Bishop::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	if (!board->getMovesTracker()->onLatestMove())
		return {};
	return board->getDiagonalMoves(atCoords, ignoreCheck);
}
