#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	bool madeFirstMove = false;
public:
	Pawn(Color withColor);
	bool isMoveValid(Board const* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const override;
};

