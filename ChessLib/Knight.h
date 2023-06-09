#pragma once
#include "Piece.h"

class Knight : public Piece
{
private:

public:
	Knight(Color withColor);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;
};

