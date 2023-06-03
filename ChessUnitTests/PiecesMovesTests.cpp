#include "CppUnitTest.h"
#include <unordered_set>
#include "../ChessLib/Board.h"
#include "../ChessLib/King.h"
#include "../ChessLib/Pawn.h"
#include "../ChessLib/Knight.h"
#include "../ChessLib/Bishop.h"
#include "../ChessLib/Rook.h"
#include "../ChessLib/Queen.h"
#include "Helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace TestHelpers;

namespace PiecesMovesTests
{
	TEST_CLASS(PiecesMovesTests)
	{
	public:
		TEST_METHOD(Board_getPawnMoves_forwardsPathClear)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			Assert::IsTrue(bothStoreSameVals({ {2,0},{3,0} }, b.getPawnMoves({ 1,0 })));
			
			b.move({ 1, 0 }, { 2, 0 });
			Assert::IsTrue(bothStoreSameVals({ {3, 0} }, b.getPawnMoves({ 2, 0 })));
		}
		TEST_METHOD(Board_getPawnMoves_forwardsPathBlocked)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			b.setPiece({ 3, 0 }, std::make_unique<Pawn>(Color::White));
			Assert::IsTrue(bothStoreSameVals({ {2,0} }, b.getPawnMoves({ 1,0 })));

			b.setPiece({ 2, 1 }, std::make_unique<Pawn>(Color::White));
			Assert::IsTrue(bothStoreSameVals({ }, b.getPawnMoves({ 1,1 })));

			b.setPiece({ 2, 5 }, std::make_unique<Pawn>(Color::Black));
			Assert::IsTrue(bothStoreSameVals({ }, b.getPawnMoves({ 1,5 })));
		}
		TEST_METHOD(Board_getPawnMoves_takes)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			b.setPiece({ 2, 0 }, std::make_unique<Pawn>(Color::White));
			b.setPiece({ 2, 2 }, std::make_unique<Pawn>(Color::White));
			Assert::IsTrue(bothStoreSameVals({ {2,0},{2,2},{2,1},{3,1} }, b.getPawnMoves({ 1,1 })));

			Board b2(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

			b.setPiece({ 2, 0 }, std::make_unique<Pawn>(Color::Black));
			b.setPiece({ 2, 2 }, std::make_unique<Pawn>(Color::White));
			Assert::IsTrue(bothStoreSameVals({ {2,2},{2,1},{3,1} }, b.getPawnMoves({ 1,1 })));
		}
		TEST_METHOD(Board_getKnightMoves_own_and_takes)
		{
			Board b(8, 8);
			b.setFenBoard("r1bqkbnr/pppp1ppp/2n5/3P4/4p3/2N5/PPP1PPPP/R1BQKBNR w KQkq - 0 4");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("a4"), parseCoords("b5"), parseCoords("b1"), parseCoords("e4") }, b.getKnightMoves(parseCoords("c3"))
			));
		}
		TEST_METHOD(Board_getKnightMoves_noone)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/p1pppppp/1p6/8/8/P1P5/1P1PPPPP/RNBQKBNR b KQkq - 0 2");

			Assert::IsTrue(bothStoreSameVals(
				{ }, b.getKnightMoves(parseCoords("b1"))
			));
		}
		TEST_METHOD(Board_getKnightMoves_would_cause_own_check)
		{
			Board b(8, 8);
			b.setFenBoard("rnb1kbnr/pp1ppppp/2p5/q7/3P4/2N5/PPP1PPPP/R1BQKBNR w KQkq - 1 3");

			Assert::IsTrue(bothStoreSameVals(
				{ }, b.getKnightMoves(parseCoords("c3"))
			));
		}
		TEST_METHOD(Board_getKnightMoves_own_king_checked)
		{
			Board b(8, 8);
			b.setFenBoard("rnb1kbnr/pp1ppppp/2p5/8/1P1P4/P1N5/2P1qPPP/R1BQKBNR w KQkq - 0 5");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e2")}, b.getKnightMoves(parseCoords("c3"))
			));
		}
		TEST_METHOD(Board_getRookMoves)
		{
			Board b(8, 8);
			Board* bp = &b;
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			std::pair<int, int> rookCoords = { 2, 0 };
			b.setPiece(rookCoords, std::make_unique<Rook>(Color::Black));

			Assert::IsTrue(
				bothStoreSameVals(
					{ {3,0}, {4,0}, {5,0}, {6,0}, {2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6}, {2,7} },
					b.getPiece(rookCoords)->getValidMoves(bp, rookCoords)
				)
			);
		}
		TEST_METHOD(Board_getBishopMoves)
		{
			Board b(8, 8);
			Board* bp = &b;
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			std::pair<int, int> bishopCoords = { 1, 1 };
			b.setPiece(bishopCoords, std::make_unique<Bishop>(Color::Black));
			auto moves = b.getPiece(bishopCoords)->getValidMoves(bp, bishopCoords);

			Assert::IsTrue(bothStoreSameVals({ {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {2,0} }, moves));
		}
	};
}
