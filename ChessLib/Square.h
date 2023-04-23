#pragma once
#include <memory>
#include "Piece.h"

class Square
{
public:
	Square() : piece(nullptr) {};

	//void setPiece(Piece& pieceToSet)
	void setPiece(std::unique_ptr<Piece> pieceToSet)
	{
		if (piece == nullptr)
		{
			piece = std::move(pieceToSet);
		}
		else
		{
			Piece* movedPiece = getPiece();
			movedPiece->gotCaptured(*movedPiece);
			piece = std::move(pieceToSet);
		}
	}

	Piece* getPiece() const
	{
		return piece.get();
	}

private:
	std::unique_ptr<Piece> piece;
};
