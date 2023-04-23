#include "Pawn.h"

Pawn::Pawn(Color withColor) : Piece(withColor)
{
    Piece::displayName = "p";
}

bool Pawn::isMoveValid(Board const* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const
{
    return true;
}
