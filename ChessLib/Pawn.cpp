#include "Pawn.h"
#include "MovesTracker.h"
#include "Board.h"
#include "King.h"

bool Pawn::isEnPassantMove(std::pair<int, int> const& move) const
{
    if (!validEnPassantLeft && !validEnPassantRight)
        return false;

    if (coordinates.second == move.second)
        return false;

    if (validEnPassantLeft && move.second == coordinates.second - 1)
        return true;

    if (validEnPassantRight && move.second == coordinates.second + 1)
        return true;

    return false;
}

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

void Pawn::setValidEnPassantLeft(bool valid)
{
    validEnPassantLeft = valid;
}

void Pawn::setValidEnPassantRight(bool valid)
{
    validEnPassantRight = valid;
}

bool Pawn::canEnPassantLeft() const
{
    return validEnPassantLeft;
}

bool Pawn::canEnPassantRight() const
{
    return validEnPassantRight;
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
    if (!board->getMovesTracker()->onLatestMove())
        return {};

    auto enPassantMoves = board->getEnPassantMoves(coordinates);
    auto standarMoves = board->getPawnMoves(atCoords, ignoreCheck);
    enPassantMoves.insert(enPassantMoves.end(), standarMoves.begin(), standarMoves.end());
    return enPassantMoves;
}

void Pawn::move(Board* board, std::pair<int, int> to)
{
    if (isEnPassantMove(to))
    {
        enPassantMove(board, to);
        return;
    }

    if (!hasMadeFirstMove() && std::abs(coordinates.first - to.first) == 2)
    {
        if (board->areCoordinatesValid({ to.first, to.second - 1 }))
        {
            if (Pawn* pLeft = dynamic_cast<Pawn*>(board->getPiece({ to.first, to.second - 1 })))
                pLeft->setValidEnPassantRight(true);
        }

        if (board->areCoordinatesValid({ to.first, to.second + 1 }))
        {
            if (Pawn* pRight = dynamic_cast<Pawn*>(board->getPiece({ to.first, to.second + 1 })))
                pRight->setValidEnPassantLeft(true);
        }
    }
    board->move(coordinates, to);
}

void Pawn::enPassantMove(Board* board, std::pair<int, int> const& to)
{
    std::pair<int, int> takenPawnCoords = { getColor() == Piece::Color::White ? to.first + 1 : to.first - 1, to.second };

    MovesTracker::Move move(
        Piece::Type::PAWN,
        Piece::Type::PAWN,
        getColor(),
        coordinates,
        to,
        true,
        King::Castle::NONE,
        { coordinates, to, takenPawnCoords },
        coordinates.second - to.second == 1 ? EnPassant::LEFT : EnPassant::RIGHT
    );
    board->getMovesTracker()->addMove(move);

    board->setPiece(to, board->setPiece(coordinates, nullptr));
    board->setPiece(takenPawnCoords, nullptr);
}
