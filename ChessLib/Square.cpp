#include "Square.h"

Piece* Square::getPiece() const
{
	return piece.get();
}

void Square::setPiece(Piece const& piece)
{
	Square::piece = std::move(std::make_unique<Piece>(piece));
}
