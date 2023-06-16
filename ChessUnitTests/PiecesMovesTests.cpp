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
		TEST_METHOD(Board_getBishopMoves_takes_and_own_on_way)
		{
			Board b(8, 8);
			Board* bp = &b;
			b.setFenBoard("rnbqkbnr/p1p1pppp/1p6/3p4/3P1B2/8/PPP1PPPP/RN1QKBNR w KQkq - 0 3");
			Assert::IsTrue(bothStoreSameVals(
				{ {1,2}, {2,3}, {3,4}, {5,6}, {2,7}, {3,6}, {5, 4}, {6, 3}, {7, 2} }, b.getPiece(parseCoords({ "f4" }))->getValidMoves(&b, b.getPiece(parseCoords({ "f4" }))->coords())
			));
		}
		TEST_METHOD(Board_getBishopMoves_no_valid_moves)
		{
			Board b(8, 8);
			Board* bp = &b;
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/5P2/8/PPPPP1PP/RNBQKBNR b KQkq - 0 1");
			Assert::IsTrue(bothStoreSameVals(
				{ }, b.getPiece(parseCoords({ "f1" }))->getValidMoves(&b, b.getPiece(parseCoords({ "f1" }))->coords())
			));
		}
		TEST_METHOD(Board_getBishopMoves_cover_check)
		{
			Board b(8, 8);
			Board* bp = &b;
			b.setFenBoard("rnb1kbnr/ppp1pppp/8/1N1p4/3Pq3/8/PPP2PPP/R1BQKBNR w KQkq - 0 5");
			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e3")}, b.getPiece(parseCoords({"c1"}))->getValidMoves(&b, b.getPiece(parseCoords({"c1"}))->coords())
			));
		}
		TEST_METHOD(Board_getBishopMoves_take_checking_piece)
		{
			Board b(8, 8);
			Board* bp = &b;
			b.setFenBoard("rnb1kbnr/ppp1pppp/8/3p4/3P4/4q3/PPP2PPP/RNBQKBNR w KQkq - 4 6");
			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e3") }, b.getPiece(parseCoords({ "c1" }))->getValidMoves(&b, b.getPiece(parseCoords({ "c1" }))->coords())
			));
		}
		TEST_METHOD(Board_getRookMoves_blocked_by_own_vertical)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppp1ppp/8/4p3/P7/8/1PPPPPPP/RNBQKBNR w KQkq - 0 2");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("a3"), parseCoords("a2") },
				b.getPiece(parseCoords("a1"))->getValidMoves(&b, parseCoords("a1"))
			));
		}
		TEST_METHOD(Board_getRookMoves_blocked_by_own_horizontal)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/ppp2ppp/8/3pp3/P7/R2P4/1PP1PPPP/1NBQKBNR b Kkq - 0 3");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("b3"), parseCoords("c3"), parseCoords("a1"), parseCoords("a2") },
				b.getPiece(parseCoords("a3"))->getValidMoves(&b, parseCoords("a3"))
			));
		}
		TEST_METHOD(Board_getRookMoves_takes)
		{
			Board b(8, 8);
			b.setFenBoard("rn1qkbnr/ppp3pp/8/3p1p2/P7/R3p2b/1PPPPPPP/1NBQKBNR w Kkq - 0 7");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("d3"), parseCoords("e3"), parseCoords("b3"), parseCoords("c3"), parseCoords("a1"), parseCoords("a2") },
				b.getPiece(parseCoords("a3"))->getValidMoves(&b, parseCoords("a3"))
			));
		}
		TEST_METHOD(Board_getRookMoves_cover_check)
		{
			Board b(8, 8);
			b.setFenBoard("r3kbnr/p3pppp/1pnpq3/1Npb4/P1PP4/R7/1P3PPP/2BQKBNR w Kkq - 1 11");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e3") },
				b.getPiece(parseCoords("a3"))->getValidMoves(&b, parseCoords("a3"))
			));
		}
		TEST_METHOD(Board_getRookMoves_take_checking_piece)
		{
			Board b(8, 8);
			b.setFenBoard("r2k1bnr/p1N1pppp/1pnp4/P1pb4/2PP4/R3q3/1P3PPP/2BQKBNR w K - 1 13");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e3") },
				b.getPiece(parseCoords("a3"))->getValidMoves(&b, parseCoords("a3"))
			));
		}
		TEST_METHOD(Board_getQueenMoves_blocked_by_own)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/p2pp1pp/1p3p2/2p5/3PP3/5P2/PPP3PP/RNBQKBNR w KQkq - 0 4");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e2"), parseCoords("d2"), parseCoords("d3") },
				b.getPiece(parseCoords("d1"))->getValidMoves(&b, parseCoords("d1"))
			));
		}
		TEST_METHOD(Board_getQueenMoves_takes)
		{
			Board b(8, 8);
			b.setFenBoard("rn1qkbnr/p3p1pp/1p1p1p2/1Np5/3PPP2/8/PPP1b1PP/R1BQKBNR w KQkq - 1 7");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e2"), parseCoords("d2"), parseCoords("d3") },
				b.getPiece(parseCoords("d1"))->getValidMoves(&b, parseCoords("d1"))
			));
		}
		TEST_METHOD(Board_getQueenMoves_cover_and_take_check)
		{
			Board b(8, 8);
			b.setFenBoard("rn2kbnr/N3p1pp/1p1p1p2/2p5/3PPP2/4Q1q1/PPP3PP/R1B1KBNR w KQkq - 1 10");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("f2"), parseCoords("g3") },
				b.getPiece(parseCoords("e3"))->getValidMoves(&b, parseCoords("e3"))
			));
		}
		TEST_METHOD(King_getValidMoves_blocked_by_own)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pp1p2pp/2p1pp2/8/8/3PPP2/PPP3PP/RNBQKBNR w KQkq - 0 4");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e2"), parseCoords("f2"), parseCoords("d2") },
				b.getPiece(parseCoords("e1"))->getValidMoves(&b, parseCoords("e1"))
			));
		}
		TEST_METHOD(King_getValidMoves_would_cause_check)
		{
			Board b(8, 8);
			b.setFenBoard("rnb1kb1r/pp1p2pp/2pqpp1n/8/8/4PP2/PPP3PP/RNBQKBNR w KQkq - 0 7");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e2"), parseCoords("f2") },
				b.getPiece(parseCoords("e1"))->getValidMoves(&b, parseCoords("e1"))
			));
		}
		TEST_METHOD(King_getValidMoves_short_castle_valid)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppp3p/5pp1/4p3/8/3BPN2/PPPP1PPP/RNBQK2R w KQkq - 0 4");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("f1"), parseCoords("e2"), parseCoords("g1") },
				b.getPiece(parseCoords("e1"))->getValidMoves(&b, parseCoords("e1"))
			));
		}
		TEST_METHOD(King_getValidMoves_short_castle_invalid_king_previously_moved)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppp3p/5pp1/4p3/8/3BPN2/PPPP1PPP/RNBQK2R w KQkq - 0 4");
			b.getPiece(parseCoords("e1"))->move(&b, parseCoords("f1"));
			b.getPiece(parseCoords("f1"))->move(&b, parseCoords("e1"));

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("f1"), parseCoords("e2") },
				b.getPiece(parseCoords("e1"))->getValidMoves(&b, parseCoords("e1"))
			));
		}
		TEST_METHOD(King_getValidMoves_short_castle_properly_set_rook)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppp3p/5pp1/4p3/8/3BPN2/PPPP1PPP/RNBQK2R w KQkq - 0 4");
			b.getPiece(parseCoords("e1"))->move(&b, parseCoords("g1"));

			Assert::AreEqual(stripFen("rnbqkbnr/pppp3p/5pp1/4p3/8/3BPN2/PPPP1PPP/RNBQ1RK1 b kq - 1 4"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(King_getValidMoves_long_castle_valid)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/2p1pppp/1p6/p2p4/5B2/2NP4/PPPQPPPP/R3KBNR w KQkq - 0 5");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("d1"), parseCoords("c1") },
				b.getPiece(parseCoords("e1"))->getValidMoves(&b, parseCoords("e1"))
			));
		}
		TEST_METHOD(King_getValidMoves_long_castle_invalid_king_previously_moved)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/2p1pppp/1p6/p2p4/5B2/2NP4/PPPQPPPP/R3KBNR w KQkq - 0 5");
			b.getPiece(parseCoords("e1"))->move(&b, parseCoords("d1"));
			b.getPiece(parseCoords("d1"))->move(&b, parseCoords("e1"));

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("d1") },
				b.getPiece(parseCoords("e1"))->getValidMoves(&b, parseCoords("e1"))
			));
		}
		TEST_METHOD(King_getValidMoves_long_castle_properly_set_rook)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/2p1pppp/1p6/p2p4/5B2/2NP4/PPPQPPPP/R3KBNR w KQkq - 0 5");
			b.getPiece(parseCoords("e1"))->move(&b, parseCoords("c1"));

			Assert::AreEqual(stripFen("rnbqkbnr/2p1pppp/1p6/p2p4/5B2/2NP4/PPPQPPPP/2KR1BNR b kq - 1 5"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(Pawn_promotion_to_queen)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::QUEEN);

			Assert::AreEqual(stripFen("Qnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(Pawn_promotion_to_knight)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::KNGIHT);

			Assert::AreEqual(stripFen("Nnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(Pawn_promotion_to_rook)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::ROOK);

			Assert::AreEqual(stripFen("Rnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(Pawn_promotion_to_bishop)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::BISHOP);

			Assert::AreEqual(stripFen("Bnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
	};
}
