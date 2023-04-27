#pragma once
#include <iostream>
#include <vector>
//#include "Board.h"


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
	Piece(Color withColor, int id) : color(withColor), displayName("x"), debugId(id) {};

	bool isMoveValid(Board* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const;

	virtual std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords) const = 0;

	void gotCaptured(Piece const& captuedBy) {};

	virtual std::string getName() const
	{
		return displayName;
	}

	Color getColor() const;

	//void setCoords(std::pair<int, int> newCoords)
	//{
	//	coords = newCoords;
	//}

protected:
	Color color;
	std::string displayName;
	int debugId;
	//std::pair<int, int> coords;
};
