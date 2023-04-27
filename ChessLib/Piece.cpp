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

std::string Piece::getName() const
{
    return (this->color == Piece::Color::White ? "w" : "b") + this->pieceSignature;
}

Piece::Color Piece::getColor() const
{
	return color;
}

void Piece::handleGotMoved()
{
    madeFirstMove = true;
}

bool Piece::hasMadeFirstMove() const
{
    return madeFirstMove;
}

