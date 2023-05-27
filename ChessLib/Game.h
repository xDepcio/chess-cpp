#pragma once
#
class Game
{
private:
	bool ai_game = false;

public:
	void run();
	void clearTerminal();
	std::pair<std::pair<int, int>, std::pair<int, int>> parseCoords(std::string coords);
	int boardCoordinateToInt(char coordinateSign) const;
	void enableAI(bool enable_ai);
};

