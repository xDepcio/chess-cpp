#pragma once
#include <memory>
#include "Piece.h"

class Square
{
public:
	Square(std::pair<int, int> coords) : piece(nullptr), coords(coords) {};

	// Returns Piece that previously occupied the square
	std::unique_ptr<Piece> setPiece(std::unique_ptr<Piece> pieceToSet);

	Piece* getPiece() const;

private:
	std::unique_ptr<Piece> piece;
	std::pair<int, int> coords;
};
