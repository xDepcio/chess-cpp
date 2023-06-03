#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>

namespace TestHelpers
{
	bool bothStoreSameVals(std::vector<std::pair<int, int>> vec1, std::vector<std::pair<int, int>> vec2);

	int boardCoordinateToInt(char coordinateSign);

	std::pair<int, int> parseCoords(std::string coords);
};

