#include "CppUnitTest.h"
#include <unordered_set>
#include "../ChessLib/Board.h"
#include "../ChessLib/King.h"
#include "../ChessLib/Pawn.h"
#include "../ChessLib/Knight.h"
#include "../ChessLib/Bishop.h"
#include "../ChessLib/Rook.h"
#include "../ChessLib/Queen.h"
#include "../ChessLib/MovesTracker.h"
#include "Helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace helperFuncsTests
{
	TEST_CLASS(helperFuncsTests)
	{
	public:
		TEST_METHOD(helper_bothStoreSameVals)
		{
			Assert::IsTrue(bothStoreSameVals({ {1, 2}, {1, 1} }, { {1, 1}, {1, 2} }));
			Assert::IsTrue(bothStoreSameVals({ {} }, { {} }));
			Assert::IsFalse(bothStoreSameVals({ {1, 2}, {1, 1} }, { {1, 1}, {1, 2}, {1, 1} }));
			Assert::IsFalse(bothStoreSameVals({ {1, 2}, {1, 1}, {1, 2} }, { {1, 1}, {1, 2}, {1, 1} }));
			Assert::IsFalse(bothStoreSameVals({ {1, 2}, {1, 1}, {1, 2} }, { {1, 1} }));
			Assert::IsFalse(bothStoreSameVals({ {1, 2} }, { {1, 1}, {1, 2}, {1, 1} }));
		}
		TEST_METHOD(helper_parseCoords)
		{
			Assert::IsTrue(std::pair<int, int>({ 7, 0 }) == std::pair<int, int>(parseCoords("a1")));
			Assert::IsTrue(std::pair<int, int>({ 1, 0 }) == std::pair<int, int>(parseCoords("a7")));
			Assert::IsTrue(std::pair<int, int>({ 5, 5 }) == std::pair<int, int>(parseCoords("f3")));
		}
		TEST_METHOD(helper_boardCoordinateToInt)
		{
			Assert::AreEqual(0, boardCoordinateToInt('a'));
			Assert::AreEqual(1, boardCoordinateToInt('b'));
			Assert::AreEqual(2, boardCoordinateToInt('c'));
			Assert::AreEqual(3, boardCoordinateToInt('d'));
			Assert::AreEqual(4, boardCoordinateToInt('e'));
			Assert::AreEqual(5, boardCoordinateToInt('f'));
			Assert::AreEqual(6, boardCoordinateToInt('g'));
			Assert::AreEqual(7, boardCoordinateToInt('h'));
			Assert::AreEqual(7, boardCoordinateToInt('1'));
			Assert::AreEqual(6, boardCoordinateToInt('2'));
			Assert::AreEqual(5, boardCoordinateToInt('3'));
			Assert::AreEqual(4, boardCoordinateToInt('4'));
			Assert::AreEqual(3, boardCoordinateToInt('5'));
			Assert::AreEqual(2, boardCoordinateToInt('6'));
			Assert::AreEqual(1, boardCoordinateToInt('7'));
			Assert::AreEqual(0, boardCoordinateToInt('8'));
		}
	};
}
