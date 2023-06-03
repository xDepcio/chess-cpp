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

namespace MovesTrackerTests
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
	};
}
