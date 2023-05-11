#pragma once
#include "Piece.h"

class Helpers
{
public:
	Helpers() {};

	static Piece::Color getOtherColor(Piece::Color color)
	{
		return color == Piece::Color::White ? Piece::Color::Black : Piece::Color::White;
	}

	template <typename T> static int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
};
