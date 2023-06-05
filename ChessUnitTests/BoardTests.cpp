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

namespace BoardTests
{
	TEST_CLASS(BoardTests)
	{
	public:
		TEST_METHOD(white_pawn_check)
		{
			Board b(8, 8);
			b.setFenBoard("rnbq1bnr/pp1kpppp/2Pp4/8/8/5N2/PPP1PPPP/RNBQKB1R b KQ - 0 4");

			Assert::IsTrue(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::Black));
		}
		TEST_METHOD(white_knight_check)
		{
			Board b(8, 8);
			b.setFenBoard("rnbq1bnr/pp1kpppp/3p4/2P1N3/8/8/PPP1PPPP/RNBQKB1R b KQ - 3 4");

			Assert::IsTrue(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::Black));
		}
		TEST_METHOD(white_bishop_check)
		{
			Board b(8, 8);
			b.setFenBoard("rnbq1b1r/pp1kpppp/3p3n/2P5/8/5NPB/PPP1PP1P/RNBQK2R b KQ - 2 5");

			Assert::IsTrue(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::Black));
		}
		TEST_METHOD(white_rook_check)
		{
			Board b(8, 8);
			b.setFenBoard("r1bq1bnr/1R1kpppp/3p4/2P5/8/5NP1/1PP1PP1P/1NBQKB1R b K - 0 10");

			Assert::IsTrue(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::Black));
		}
		TEST_METHOD(white_queen_check)
		{
			Board b(8, 8);
			b.setFenBoard("rnbq1bnr/pp1kpppp/3Q4/2P5/8/5N2/PPP1PPPP/RNB1KB1R b KQ - 0 4");

			Assert::IsTrue(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::Black));
		}
		TEST_METHOD(white_queen_checkMate)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqr3/pp1k3p/3QpppN/2P5/8/8/PPP1PPPP/RNB1KB1R b KQ - 0 17");

			Assert::IsTrue(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));
			Assert::IsFalse(b.isCheckMate(Color::White));
			Assert::IsTrue(b.isCheckMate(Color::Black));
		}
		TEST_METHOD(Board_isStalemate)
		{
			Board b(8, 8);
			b.setFenBoard("k7/2Q5/2R5/8/P3P3/8/1PP2PPP/1NB1KBNR b K - 8 27");

			Assert::IsTrue(b.isStalemate(Color::Black));
		}
	};
}
