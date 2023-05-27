#pragma once
#include "Constants.h"

class Game
{
private:
	bool ai_game = false;
	Color human_color = Color::White;

public:
	void run();
	void clearTerminal();
	std::pair<std::pair<int, int>, std::pair<int, int>> parseCoords(std::string coords);
	int boardCoordinateToInt(char coordinateSign) const;
	void enableAI(bool enable_ai);
	void setAIcolor(Color color);
};

