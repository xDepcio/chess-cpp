#include "Rook.h"
#include "MovesTracker.h"
#include "Board.h"

Rook::Rook(Color withColor) : Piece(withColor)
{
    Piece::pieceSignature = "r";
    type = Type::ROOK;
}

Rook::Rook(Color withColor, int id) : Piece(withColor, id)
{
    Piece::pieceSignature = "r";
    type = Type::ROOK;
}

std::vector<std::pair<int, int>> Rook::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
    if (!board->getMovesTracker()->onLatestMove())
        return {};
    std::vector<std::pair<int, int>> moves;
    auto horizontalMoves = board->getHorizontalMoves(atCoords, ignoreCheck);
    moves.insert(moves.end(), horizontalMoves.begin(), horizontalMoves.end());

    auto verticalMoves = board->getVerticalMoves(atCoords, ignoreCheck);
    moves.insert(moves.end(), verticalMoves.begin(), verticalMoves.end());

    return moves;
}
