#pragma once
#include "Metadata.h"
#include "Piece.h"
#include "Pawn.h"
#include <memory>

class Square
{
private:
	metadata::Color color;
	std::unique_ptr<Piece> piece;
public:
	Square(metadata::Color squareColor) : piece(nullptr), color(squareColor) {};
	
	Piece* getPiece() const;
	void setPiece(Piece const& piece);
};

