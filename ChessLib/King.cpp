#include "King.h"
#include "Board.h"
#include "Helpers.h"
#include "MovesTracker.h"
#include "Helpers.h"

King::King(Color withColor) : Piece(withColor)
{
	Piece::pieceSignature = withColor == Color::Black ? "k" : "K";
	Piece::type = PieceType::KING;
}

std::vector<std::pair<int, int>> King::getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck) const
{
	if (!board->getMovesTracker()->onLatestMove())
		return {};

	auto validMoves = board->getKingMoves(atCoords, ignoreCheck);
	auto casteMoves = board->getCastleMoves(color);
	for (auto& mv : casteMoves)
	{
		validMoves.push_back(mv);
	}
	return validMoves;
}

void King::move(Board* board, std::pair<int, int> to)
{
	if (std::abs(coordinates.second - to.second) > 1)
		castleMove(board, { coordinates.first, to.second == 2 ? 0 : 7 });
	else
		board->move(coordinates, to);
}

void King::castleMove(Board* board, std::pair<int, int> rookCoords)
{
	auto oldCoords = coordinates;
	int dirSign = Helpers::sgn<int>(oldCoords.second - rookCoords.second);

	std::pair<int, int> newKingCoords = { 
		coordinates.first, 
		coordinates.second - 2 * dirSign
	};

	std::pair<int, int> newRookCoords = {
		coordinates.first,
		newKingCoords.second + dirSign
	};

	board->setPiece(newKingCoords, board->setPiece(coordinates, nullptr));
	board->setPiece(newRookCoords, board->setPiece(rookCoords, nullptr));
	setMadeFirstMove(true);


	auto mvPtr = std::make_unique<MovesTracker::Move>(
		PieceType::KING,
		PieceType::NONE,
		nullptr,
		color,
		oldCoords,
		coordinates,
		false,
		dirSign == 1 ? Castle::LONG : Castle::SHORT,
		std::vector<std::pair<int, int>>({ oldCoords, rookCoords, coordinates, newRookCoords }),
		EnPassant::NONE,
		board->isCheck(Helpers::getOtherColor(color))
	);

	board->getMovesTracker()->addMove(std::move(mvPtr));
	
}
