#include "Bishop.h"

Bishop::Bishop(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "b";
}

Bishop::Bishop(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = "b";
}

std::vector<std::pair<int, int>> Bishop::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	return board->getDiagonalMoves(atCoords, ignoreCheck);
}
