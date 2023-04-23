#pragma once
#include <memory>
#include "Piece.h"

class Square
{
public:
	Square() : piece(nullptr) {};

	void setPiece(Piece& pieceToSet)
	{
		if (piece == nullptr)
		{
			piece = std::move(std::make_unique<Piece>(pieceToSet));
		}
		else
		{
			Piece* movedPiece = getPiece();
			movedPiece->gotCaptured(pieceToSet);
			piece = std::move(std::make_unique<Piece>(pieceToSet));
		}
	}

	Piece* getPiece()
	{
		return piece.get();
	}

private:
	std::unique_ptr<Piece> piece;
};
