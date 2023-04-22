#pragma once
#include "Metadata.h"
#include "Piece.h"
#include "Pawn.h"
class Square
{
private:
	metadata::Color color;
	Piece piece;
public:
	Square(metadata::Color color) : color(color), piece(Pawn(Color::White)) {};
	
	Piece getPiece() const;
	void setPiece(const Piece& piece);
};

