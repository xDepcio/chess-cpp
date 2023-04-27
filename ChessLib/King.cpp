#include "King.h"

King::King(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "K";
}

std::vector<std::pair<int, int>> King::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
{
	return board->getKingMoves(atCoords);
}
