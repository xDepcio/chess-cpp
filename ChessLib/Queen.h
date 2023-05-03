#pragma once
#include "Piece.h"
#include "Board.h"

class Queen : public Piece
{
private:

public:
	Queen(Color withColor);
	Queen(Color withColor, int id);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;

};

