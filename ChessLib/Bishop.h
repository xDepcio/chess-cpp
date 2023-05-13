#pragma once
#include "Piece.h"
//#include "Board.h"
class Board;

class Bishop : public Piece
{
private:

public:
	Bishop(Color withColor);
	Bishop(Color withColor, int id);

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;

};
