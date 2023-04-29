#pragma once
#include "Piece.h"
#include "Board.h"

class King : public Piece
{
private:

public:
	King(Color withColor);
	//King(Color withColor, int id);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;
};

