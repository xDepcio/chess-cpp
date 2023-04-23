#include "Pawn.h"

Pawn::Pawn(Color withColor) : Piece(withColor)
{
    Piece::displayName = "p";
}

bool Pawn::isMoveValid(Board const* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const
{
    return true;
}

std::vector<std::pair<int, int>> Pawn::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
{
    return board->getPawnMoves(atCoords);
}

bool Pawn::hasMadeFirstMove() const
{
    return madeFirstMove;
}
