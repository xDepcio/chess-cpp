#pragma once
#include <iostream>
#include "Board.h"
#include <vector>
#include <iomanip>
#include <sstream>

class Game
{
public:
	void run();
	void clearTerminal();
	std::pair<std::pair<int, int>, std::pair<int, int>> parseCoords(std::string coords);
};

