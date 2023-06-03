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

namespace MovesTrackerTests
{
	TEST_CLASS(MovesTrackerTests)
	{
	public:
		TEST_METHOD(MovesTracker_getMoveCount_empty_at_start)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			Assert::AreEqual(0, b.getMovesTracker()->getMoveCount());
		}
		TEST_METHOD(MovesTracker_getMoveCount_increase_properly)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			Assert::AreEqual(0, b.getMovesTracker()->getMoveCount());
		}
	};
}
