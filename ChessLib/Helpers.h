#pragma once
#include "Piece.h"

class Helpers
{
public:
	Helpers() {};

	static Color getOtherColor(Color color)
	{
		return color == Color::White ? Color::Black : Color::White;
	}

	template <typename T> static int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}
};
