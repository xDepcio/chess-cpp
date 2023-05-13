#pragma once
#include "Piece.h"

class Rook : public Piece
{
private:

public:
	Rook(Color withColor);
	Rook(Color withColor, int id);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;

};
