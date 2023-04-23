#pragma once
#include <memory>
#include "Piece.h"

class Square
{
public:
	Square() : piece(nullptr) {};

	//void setPiece(Piece& pieceToSet)
	std::unique_ptr<Piece> setPiece(std::unique_ptr<Piece> pieceToSet)
	{
		// Returns Piece that previously occupied the square
		std::unique_ptr<Piece> old = std::move(piece);
		piece = std::move(pieceToSet);

		return old;
		//if (piece == nullptr)
		//{
		//	piece = std::move(pieceToSet);
		//}
		//else
		//{
		//	Piece* movedPiece = getPiece();
		//	movedPiece->gotCaptured(*movedPiece);
		//	piece = std::move(pieceToSet);
		//}
	}

	Piece* getPiece() const
	{
		return piece.get();
	}

private:
	std::unique_ptr<Piece> piece;
};
