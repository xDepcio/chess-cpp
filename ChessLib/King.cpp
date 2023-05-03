#include "King.h"

King::King(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "K";
}

King::King(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = "K";
}



std::vector<std::pair<int, int>> King::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	return board->getKingMoves(atCoords, ignoreCheck);
}
