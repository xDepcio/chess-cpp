#include "Pawn.h"

Pawn::Pawn(Color withColor) : Piece(withColor)
{
    Piece::pieceSignature = "p";
    type = Type::PAWN;
}
Pawn::Pawn(Color withColor, int id) : Piece(withColor, id)
{
    Piece::pieceSignature = "p";
    type = Type::PAWN;
}

//bool Pawn::isMoveValid(Board* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const
//{
//    std::vector<std::pair<int, int>> validMoves = this->getValidMoves(board, from);
//    for (auto& move : validMoves)
//    {
//        if (move == to)
//        {
//            return true;
//        }
//    }
//
//    return false;
//}

std::vector<std::pair<int, int>> Pawn::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
    return board->getPawnMoves(atCoords, ignoreCheck);
}
