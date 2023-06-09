#include "Pawn.h"
#include "MovesTracker.h"
#include "Board.h"
#include "King.h"
#include "Helpers.h"

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

void Pawn::promotionMove(Board* board, std::pair<int, int> const& to)
{

}

Pawn::Pawn(Color withColor) : Piece(withColor)
{
    Piece::pieceSignature = withColor == Color::Black ? "p" : "P";
    type = PieceType::PAWN;
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
    if (to.first == 0 || to.first == 7)
    {
        board->requestPromotionChoice(coordinates, to);
        //promotionMove(board, to);
        return;
    }

    if (isEnPassantMove(to))
    {
        enPassantMove(board, to);
        board->invalidateEnPassantes(color);
        return;
    }

    // sets posibility for other pawns for enpassant
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
    std::pair<int, int> takenPawnCoords = { getColor() == Color::White ? to.first + 1 : to.first - 1, to.second };

    auto movePtr = std::make_unique<MovesTracker::Move>(
        PieceType::PAWN,
        PieceType::PAWN,
        board->getPieceUniquePtr(takenPawnCoords),
        getColor(),
        coordinates,
        to,
        true,
        Castle::NONE,
        std::vector<std::pair<int, int>>({ coordinates, to, takenPawnCoords }),
        coordinates.second - to.second == 1 ? EnPassant::LEFT : EnPassant::RIGHT,
        board->isCheck(Helpers::getOtherColor(getColor()))
    );
    board->getMovesTracker()->addMove(std::move(movePtr));

    board->setPiece(to, board->setPiece(coordinates, nullptr));
    board->setPiece(takenPawnCoords, nullptr);
}
