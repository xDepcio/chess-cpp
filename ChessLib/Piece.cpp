#include "Piece.h"

class Board;

bool Piece::isMoveValid(Board const* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const
{
	return false;
}

std::vector<std::pair<int, int>> Piece::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
{
	return std::vector<std::pair<int, int>>();
}

//std::vector<std::pair<int, int>> Piece::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
//{
//	return std::vector<std::pair<int, int>>();
//}

Piece::Color Piece::getColor() const
{
	return color;
}

