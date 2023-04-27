#pragma once
#include "Piece.h"
#include "Board.h"

class Pawn : public Piece
{
private:

public:
	Pawn(Color withColor);
	Pawn(Color withColor, int id);
	//bool isMoveValid(Board* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const override;

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords) const override;
};

