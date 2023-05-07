#include "King.h"

King::King(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "K";
	Piece::type = Type::KING;
}

King::King(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = "K";
	Piece::type = Type::KING;
}



std::vector<std::pair<int, int>> King::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	return board->getKingMoves(atCoords, ignoreCheck);
}
