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
			b.move(parseCoords("b2"), parseCoords("b4"));
			b.move(parseCoords("b7"), parseCoords("b5"));

			Assert::AreEqual(2, b.getMovesTracker()->getMoveCount());
		}
		TEST_METHOD(MovesTracker_prev_next_doesnt_change_move_count)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			b.move(parseCoords("b2"), parseCoords("b4"));
			b.move(parseCoords("b7"), parseCoords("b5"));
			b.getMovesTracker()->previous();

			Assert::AreEqual(2, b.getMovesTracker()->getMoveCount());
			b.getMovesTracker()->next();
			Assert::AreEqual(2, b.getMovesTracker()->getMoveCount());
		}
		TEST_METHOD(MovesTracker_prev_pawn_moves)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			b.move(parseCoords("b2"), parseCoords("b4"));
			b.move(parseCoords("b7"), parseCoords("b5"));
			b.getMovesTracker()->previous();
			b.getMovesTracker()->previous();

			Assert::AreEqual(std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_pawn_takes)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			b.move(parseCoords("d2"), parseCoords("d4"));
			b.move(parseCoords("e7"), parseCoords("e5"));
			b.move(parseCoords("d4"), parseCoords("e5"));
			b.getMovesTracker()->previous();

			Assert::AreEqual(std::string("rnbqkbnr/pppp1ppp/8/4p3/3P4/8/PPP1PPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_short_castle)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqk2r/pppp1ppp/3bpn2/8/8/3BPN2/PPPP1PPP/RNBQK2R w KQkq - 2 4");
			b.getPiece(parseCoords("e1"))->move(&b, parseCoords("g1"));
			b.getMovesTracker()->previous();

			Assert::AreEqual(std::string("rnbqk2r/pppp1ppp/3bpn2/8/8/3BPN2/PPPP1PPP/RNBQK2R"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_long_castle)
		{
			Board b(8, 8);
			b.setFenBoard("r1bqkbnr/ppp3pp/2n1pp2/3p4/8/2NPB3/PPPQPPPP/R3KBNR w KQkq - 0 5");
			b.getPiece(parseCoords("e1"))->move(&b, parseCoords("c1"));
			b.getMovesTracker()->previous();

			Assert::AreEqual(std::string("r1bqkbnr/ppp3pp/2n1pp2/3p4/8/2NPB3/PPPQPPPP/R3KBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_knight_move)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			b.move(parseCoords("b1"), parseCoords("c3"));
			b.getMovesTracker()->previous();

			Assert::AreEqual(std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_knight_takes)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkbnr/pp1ppppp/8/5P2/8/2p2N2/PPPPP1PP/RNBQKB1R w KQkq - 0 4");
			b.move(parseCoords("b1"), parseCoords("c3"));
			b.getMovesTracker()->previous();

			Assert::AreEqual(std::string("rnbqkbnr/pp1ppppp/8/5P2/8/2p2N2/PPPPP1PP/RNBQKB1R"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_revert_pawn_promotion_to_queen)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::QUEEN);
			
			Assert::AreEqual(std::string("Qnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
			
			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_next_make_pawn_promotion_to_queen)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::QUEEN);

			Assert::AreEqual(std::string("Qnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		
			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		
			b.getMovesTracker()->next();
			Assert::AreEqual(std::string("Qnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_revert_pawn_promotion_to_knight)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::KNGIHT);

			Assert::AreEqual(std::string("Nnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_next_make_pawn_promotion_to_knight)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::KNGIHT);

			Assert::AreEqual(std::string("Nnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->next();
			Assert::AreEqual(std::string("Nnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_revert_pawn_promotion_to_rook)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::ROOK);

			Assert::AreEqual(std::string("Rnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_next_make_pawn_promotion_to_rook)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::ROOK);

			Assert::AreEqual(std::string("Rnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->next();
			Assert::AreEqual(std::string("Rnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_prev_revert_pawn_promotion_to_bishop)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::BISHOP);

			Assert::AreEqual(std::string("Bnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
		TEST_METHOD(MovesTracker_next_make_pawn_promotion_to_bishop)
		{
			Board b(8, 8);
			b.setFenBoard("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR w KQkq - 1 5");
			b.getPiece(parseCoords("b7"))->move(&b, parseCoords("a8"));
			b.receivePromotionChoice(Promotions::BISHOP);

			Assert::AreEqual(std::string("Bnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->previous();
			Assert::AreEqual(std::string("rnbqkb1r/1P1ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));

			b.getMovesTracker()->next();
			Assert::AreEqual(std::string("Bnbqkb1r/3ppppp/p4n2/8/8/8/P1PPPPPP/RNBQKBNR"), stripFen(b.getFenBoard()));
		}
	};
}
