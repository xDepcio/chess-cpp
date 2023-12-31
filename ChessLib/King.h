#pragma once
#include "Piece.h"

class King : public Piece
{
private:

public:
	King(Color withColor);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;
	virtual void move(Board* board, std::pair<int, int> to) override;
	void castleMove(Board* board, std::pair<int, int> rookCoords);
};

