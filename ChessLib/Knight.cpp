#include "Knight.h"

Knight::Knight(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "k";
}

Knight::Knight(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = "k";
}

std::vector<std::pair<int, int>> Knight::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
{
	return board->getKnightMoves(atCoords);
}
