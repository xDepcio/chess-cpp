#pragma once

class Game
{
public:
	void run();
	void clearTerminal();
	std::pair<std::pair<int, int>, std::pair<int, int>> parseCoords(std::string coords);
	int boardCoordinateToInt(char coordinateSign) const;
};

