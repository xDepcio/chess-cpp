#pragma once
#include <iostream>
#include "Board.h"
#include <vector>
#include <iomanip>
#include <sstream>
#include "Knight.h"

class Game
{
public:
	void run();
	void clearTerminal();
	std::pair<std::pair<int, int>, std::pair<int, int>> parseCoords(std::string coords);
	int boardCoordinateToInt(char coordinateSign) const;
};

