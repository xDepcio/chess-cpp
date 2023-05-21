#include "Bishop.h"
#include "MovesTracker.h"
#include "Board.h"

Bishop::Bishop(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = withColor == Piece::Color::Black ? "b" : "B";
	Piece::type = Type::BISHOP;
}

Bishop::Bishop(Color withColor, int id) : Piece(withColor, id)
{
	Piece::pieceSignature = withColor == Piece::Color::Black ? "b" : "B";
	Piece::type = Type::BISHOP;
}

std::vector<std::pair<int, int>> Bishop::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	if (!board->getMovesTracker()->onLatestMove())
		return {};
	return board->getDiagonalMoves(atCoords, ignoreCheck);
}
