#include "Queen.h"

Queen::Queen(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = "q";
    type = Type::QUEEN;
}

Queen::Queen(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = "q";
    type = Type::QUEEN;
}

std::vector<std::pair<int, int>> Queen::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
    if (!board->getMovesTracker()->onLatestMove())
        return {};
    std::vector<std::pair<int, int>> moves;
    auto horizontalMoves = board->getHorizontalMoves(atCoords, ignoreCheck);
    moves.insert(moves.end(), horizontalMoves.begin(), horizontalMoves.end());

    auto verticalMoves = board->getVerticalMoves(atCoords, ignoreCheck);
    moves.insert(moves.end(), verticalMoves.begin(), verticalMoves.end());

    auto diagonalMoves = board->getDiagonalMoves(atCoords, ignoreCheck);
    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());

    return moves;
}
