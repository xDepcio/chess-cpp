#include "Piece.h"

class Board;

bool Piece::isMoveValid(Board* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const
{
    std::vector<std::pair<int, int>> validMoves = this->getValidMoves(board, from);
    for (auto& move : validMoves)
    {
        if (move == to)
        {
            return true;
        }
    }

    return false;
}
//
//std::vector<std::pair<int, int>> Piece::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
//{
//	return std::vector<std::pair<int, int>>();
//}

//std::vector<std::pair<int, int>> Piece::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
//{
//	return std::vector<std::pair<int, int>>();
//}

Piece::Color Piece::getColor() const
{
	return color;
}

