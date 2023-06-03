#include "Helpers.h"

#ifndef CHESS_TEST_HELPERS
#define CHESS_TEST_HELPERS

int boardCoordinateToInt(char coordinateSign)
	{
		if (coordinateSign <= 57) // "9" is 57 in ASCI
		{
			return 7 - (coordinateSign - 49);
		}
		else
		{
			return coordinateSign - 97;
		}
	}

namespace TestHelpers
{
	bool bothStoreSameVals(std::vector<std::pair<int, int>> vec1, std::vector<std::pair<int, int>> vec2)
	{
		if (vec1.size() != vec2.size())
			return false;

		std::unordered_set<int> burnedIndexes;

		for (auto& val1 : vec1)
		{
			int vec2Index = 0;
			bool isIn = false;
			for (auto& val2 : vec2)
			{
				if (val1 == val2 && burnedIndexes.count(vec2Index) == 0)
				{
					isIn = true;
					burnedIndexes.insert(vec2Index);
					break;
				}
				vec2Index++;
			}


			if (!isIn)
				return false;
		}

		return true;
	}


	std::pair<int, int> parseCoords(std::string coords)
	{
		return { boardCoordinateToInt(coords[1]), boardCoordinateToInt(coords[0]) };
	}
};

#endif /*CHESS_TEST_HELPERS*/

