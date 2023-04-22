#pragma once
#include "Metadata.h"

using namespace metadata;

class Piece
{
private:
	Color color;
public:
	Piece() : color(Color::White) {};
	Piece(Color pieceColor);
};

