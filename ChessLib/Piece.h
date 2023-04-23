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
	Piece(Color withColor) : color(withColor), displayName("x") {};

	virtual bool isMoveValid(Board const* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const;

	void gotCaptured(Piece const& captuedBy) {};

	virtual std::string getName() const
	{
		return ":(";
	}


protected:
	Color color;
	std::string displayName;
};
