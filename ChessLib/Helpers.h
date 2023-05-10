#pragma once
#include "Piece.h"

namespace helpers {
	Piece::Color otherColor(Piece::Color color)
	{
		return color == Piece::Color::White ? Piece::Color::Black : Piece::Color::White;
	}
}
