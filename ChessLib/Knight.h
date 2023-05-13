#pragma once
#include "Piece.h"
//#include "Board.h"

class Knight : public Piece
{
private:

public:
	Knight(Color withColor);
	Knight(Color withColor, int id);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;
};

