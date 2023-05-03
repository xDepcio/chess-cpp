#include "Square.h"

std::unique_ptr<Piece> Square::setPiece(std::unique_ptr<Piece> pieceToSet)
{
	// Returns Piece that previously occupied the square
	std::unique_ptr<Piece> old = std::move(piece);
	piece = std::move(pieceToSet);

	if (old != nullptr)
	{
		old->handleGotTaken(piece.get());
	}

	return old;
}

Piece* Square::getPiece() const
{
	return piece.get();
}
