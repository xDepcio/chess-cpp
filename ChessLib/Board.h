#pragma once
#include "Square.h"
#include "Metadata.h"
#include <vector>

using namespace metadata;

class Board
{
private:
	std::vector<std::vector<Square>> squares;

public:
	Board();
	Board(std::vector<std::vector<Square>> startingPlacement);

	void setPiece(Piece const& piece, std::pair<int, int> cords);
};

