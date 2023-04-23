#pragma once
#include <iostream>
#include "Board.h"
#include <string>

class Game
{
public:
	void run();
	void clearTerminal();
	std::pair<std::pair<int, int>, std::pair<int, int>> parseCoords(std::string coords);
};

