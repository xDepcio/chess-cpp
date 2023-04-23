#pragma once
#include <iostream>


class Board;

class Piece
{
public:
	enum class Color
	{
		White,
		Black
	};
	//Piece(Color withColor, std::pair<int, int> startCoords) : color(withColor), coords(startCoords) {};
	Piece(Color withColor) : color(withColor) {};

	virtual bool isMoveValid(Board const* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const
	{
		return false;
	}

	void gotCaptured(Piece const& captuedBy);

	//void move(std::pair<int, int> toCoords);

protected:
	Color color;
	//std::pair<int, int> coords;
};
