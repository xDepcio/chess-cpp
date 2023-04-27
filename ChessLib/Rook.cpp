#include "Rook.h"

Rook::Rook(Color withColor) : Piece(withColor)
{
    Piece::pieceSignature = "r";
}

Rook::Rook(Color withColor, int id) : Piece(withColor, id)
{
    Piece::pieceSignature = "r";
}

std::vector<std::pair<int, int>> Rook::getValidMoves(Board* board, std::pair<int, int> const& atCoords) const
{
    std::vector<std::pair<int, int>> moves;
    auto horizontalMoves = board->getHorizontalMoves(atCoords);
    moves.insert(moves.end(), horizontalMoves.begin(), horizontalMoves.end());

    auto verticalMoves = board->getVerticalMoves(atCoords);
    moves.insert(moves.end(), verticalMoves.begin(), verticalMoves.end());

    return moves;
}
