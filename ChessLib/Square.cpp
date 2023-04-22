#include "Square.h"

void Square::setPiece(const Piece& piece)
{
	Square::piece = piece;
}

Piece Square::getPiece() const
{
	return piece;
}
