#pragma once
#include "Piece.h"

class Board;

class Queen : public Piece
{
private:

public:
	Queen(Color withColor);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;

};

