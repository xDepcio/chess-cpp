#include "Knight.h"

Knight::Knight(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "k";
	type = Type::KNIGHT;
}

Knight::Knight(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = "k";
	type = Type::KNIGHT;
}

std::vector<std::pair<int, int>> Knight::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	return board->getKnightMoves(atCoords, ignoreCheck);
}
