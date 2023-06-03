#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>

int boardCoordinateToInt(char coordinateSign);

namespace TestHelpers
{
	bool bothStoreSameVals(std::vector<std::pair<int, int>> vec1, std::vector<std::pair<int, int>> vec2);


	std::pair<int, int> parseCoords(std::string coords);
};

