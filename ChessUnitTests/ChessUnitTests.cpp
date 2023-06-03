#include "pch.h"
#include "CppUnitTest.h"
#include <unordered_set>
#include "../ChessLib/Board.h"
#include "../ChessLib/King.h"
#include "../ChessLib/Pawn.h"
#include "../ChessLib/Knight.h"
#include "../ChessLib/Bishop.h"
#include "../ChessLib/Rook.h"
#include "../ChessLib/Queen.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

enum class BoardPresets
{
	STANDARD,
	MIDGAME_1,
	CHECK,
	ENDGAME_1
};

void presetBoard(Board& board, BoardPresets preset)
{
	switch (preset)
	{
	case BoardPresets::STANDARD:
	{
		board.setPiece({ 1, 0 }, std::make_unique<Pawn>(Color::Black, 201));
		board.setPiece({ 1, 1 }, std::make_unique<Pawn>(Color::Black, 202));
		board.setPiece({ 1, 2 }, std::make_unique<Pawn>(Color::Black, 203));
		board.setPiece({ 1, 3 }, std::make_unique<Pawn>(Color::Black, 204));
		board.setPiece({ 1, 4 }, std::make_unique<Pawn>(Color::Black, 205));
		board.setPiece({ 1, 5 }, std::make_unique<Pawn>(Color::Black, 206));
		board.setPiece({ 1, 6 }, std::make_unique<Pawn>(Color::Black, 207));
		board.setPiece({ 1, 7 }, std::make_unique<Pawn>(Color::Black, 208));

		board.setPiece({ 0, 1 }, std::make_unique<Knight>(Color::Black, 211));
		board.setPiece({ 0, 6 }, std::make_unique<Knight>(Color::Black, 212));

		board.setPiece({ 0, 2 }, std::make_unique<Bishop>(Color::Black, 242));
		board.setPiece({ 0, 5 }, std::make_unique<Bishop>(Color::Black, 242));

		board.setPiece({ 0, 0 }, std::make_unique<Rook>(Color::Black, 221));
		board.setPiece({ 0, 7 }, std::make_unique<Rook>(Color::Black, 222));

		board.setPiece({ 0, 4 }, std::make_unique<King>(Color::Black, 231));

		board.setPiece({ 0, 3 }, std::make_unique<Queen>(Color::Black, 251));


		board.setPiece({ 6, 0 }, std::make_unique<Pawn>(Color::White, 101));
		board.setPiece({ 6, 1 }, std::make_unique<Pawn>(Color::White, 102));
		board.setPiece({ 6, 2 }, std::make_unique<Pawn>(Color::White, 103));
		board.setPiece({ 6, 3 }, std::make_unique<Pawn>(Color::White, 104));
		board.setPiece({ 6, 4 }, std::make_unique<Pawn>(Color::White, 105));
		board.setPiece({ 6, 5 }, std::make_unique<Pawn>(Color::White, 106));
		board.setPiece({ 6, 6 }, std::make_unique<Pawn>(Color::White, 107));
		board.setPiece({ 6, 7 }, std::make_unique<Pawn>(Color::White, 108));

		board.setPiece({ 7, 1 }, std::make_unique<Knight>(Color::White, 111));
		board.setPiece({ 7, 6 }, std::make_unique<Knight>(Color::White, 112));

		board.setPiece({ 7, 2 }, std::make_unique<Bishop>(Color::White, 142));
		board.setPiece({ 7, 5 }, std::make_unique<Bishop>(Color::White, 142));

		board.setPiece({ 7, 0 }, std::make_unique<Rook>(Color::White, 121));
		board.setPiece({ 7, 7 }, std::make_unique<Rook>(Color::White, 122));

		board.setPiece({ 7, 4 }, std::make_unique<King>(Color::White, 131));

		board.setPiece({ 7, 3 }, std::make_unique<Queen>(Color::White, 151));
		break;
	}
	case BoardPresets::CHECK:
	{
		board.setPiece({ 1, 0 }, std::make_unique<Pawn>(Color::Black, 201));
		board.setPiece({ 1, 1 }, std::make_unique<Pawn>(Color::Black, 202));
		board.setPiece({ 1, 2 }, std::make_unique<Pawn>(Color::Black, 203));
		board.setPiece({ 1, 3 }, std::make_unique<Pawn>(Color::Black, 204));
		board.setPiece({ 1, 4 }, std::make_unique<Pawn>(Color::Black, 205));
		board.setPiece({ 3, 5 }, std::make_unique<Pawn>(Color::Black, 206));
		board.setPiece({ 1, 6 }, std::make_unique<Pawn>(Color::Black, 207));
		board.setPiece({ 1, 7 }, std::make_unique<Pawn>(Color::Black, 208));

		board.setPiece({ 0, 1 }, std::make_unique<Knight>(Color::Black, 211));
		board.setPiece({ 0, 6 }, std::make_unique<Knight>(Color::Black, 212));

		board.setPiece({ 0, 2 }, std::make_unique<Bishop>(Color::Black, 242));
		board.setPiece({ 0, 5 }, std::make_unique<Bishop>(Color::Black, 242));

		board.setPiece({ 0, 0 }, std::make_unique<Rook>(Color::Black, 221));
		board.setPiece({ 0, 7 }, std::make_unique<Rook>(Color::Black, 222));

		board.setPiece({ 0, 4 }, std::make_unique<King>(Color::Black, 231));

		board.setPiece({ 0, 3 }, std::make_unique<Queen>(Color::Black, 251));


		board.setPiece({ 6, 0 }, std::make_unique<Pawn>(Color::White, 101));
		board.setPiece({ 6, 1 }, std::make_unique<Pawn>(Color::White, 102));
		board.setPiece({ 6, 2 }, std::make_unique<Pawn>(Color::White, 103));
		board.setPiece({ 6, 3 }, std::make_unique<Pawn>(Color::White, 104));
		board.setPiece({ 4, 4 }, std::make_unique<Pawn>(Color::White, 105));
		board.setPiece({ 6, 5 }, std::make_unique<Pawn>(Color::White, 106));
		board.setPiece({ 6, 6 }, std::make_unique<Pawn>(Color::White, 107));
		board.setPiece({ 6, 7 }, std::make_unique<Pawn>(Color::White, 108));

		board.setPiece({ 7, 1 }, std::make_unique<Knight>(Color::White, 111));
		board.setPiece({ 7, 6 }, std::make_unique<Knight>(Color::White, 112));

		board.setPiece({ 7, 2 }, std::make_unique<Bishop>(Color::White, 142));
		board.setPiece({ 7, 5 }, std::make_unique<Bishop>(Color::White, 142));

		board.setPiece({ 7, 0 }, std::make_unique<Rook>(Color::White, 121));
		board.setPiece({ 7, 7 }, std::make_unique<Rook>(Color::White, 122));

		board.setPiece({ 7, 4 }, std::make_unique<King>(Color::White, 131));

		board.setPiece({ 3, 7 }, std::make_unique<Queen>(Color::White, 151));
		break;
	}
	default:
		break;
	}
}

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

std::pair<int, int> parseCoords(std::string coords)
{
	return { boardCoordinateToInt(coords[1]), boardCoordinateToInt(coords[0]) };
}


namespace ChessUnitTests
{
	TEST_CLASS(helpterFuncsTests)
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

	TEST_CLASS(BoardUnitTests)
	{
	public:
		class Board_ : private Board
		{
			Board_(int w, int h) : Board(w, h) {};
			friend BoardUnitTests;
		};
		
		TEST_METHOD(Board_getPawnMoves_forwardsPathClear)
		{
			Board b(8, 8);
			presetBoard(b, BoardPresets::STANDARD);

			Assert::IsTrue(bothStoreSameVals({ {2,0},{3,0} }, b.getPawnMoves({ 1,0 })));
			
			b.move({ 1, 0 }, { 2, 0 });
			Assert::IsTrue(bothStoreSameVals({ {3, 0} }, b.getPawnMoves({ 2, 0 })));
		}
		TEST_METHOD(Board_getPawnMoves_forwardsPathBlocked)
		{
			Board b(8, 8);
			presetBoard(b, BoardPresets::STANDARD);

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
			presetBoard(b, BoardPresets::STANDARD);

			b.setPiece({ 2, 0 }, std::make_unique<Pawn>(Color::White));
			b.setPiece({ 2, 2 }, std::make_unique<Pawn>(Color::White));
			Assert::IsTrue(bothStoreSameVals({ {2,0},{2,2},{2,1},{3,1} }, b.getPawnMoves({ 1,1 })));

			Board b2(8, 8);
			presetBoard(b2, BoardPresets::STANDARD);

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
		TEST_METHOD(Board_getKnightMoves_own_king_checked)
		{
			Board b(8, 8);
			b.setFenBoard("rnb1kbnr/pp1ppppp/2p5/8/1P1P4/P1N5/2P1qPPP/R1BQKBNR w KQkq - 0 5");

			Assert::IsTrue(bothStoreSameVals(
				{ parseCoords("e2") }, b.getKnightMoves(parseCoords("c3"))
			));
		}
		TEST_METHOD(Board_isCheck)
		{
			Board b(8, 8);
			presetBoard(b, BoardPresets::CHECK);

			Assert::IsTrue(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));

			b.move({ 1,6 }, { 2,6 });
			Assert::IsFalse(b.isCheck(Color::Black));
			Assert::IsFalse(b.isCheck(Color::White));
		}
		TEST_METHOD(Board_getPawnMoves_pinned)
		{
			Board b(8, 8);
			presetBoard(b, BoardPresets::CHECK);
			b.move({ 1,6 }, { 2,6 });

			Assert::IsTrue(bothStoreSameVals({ {3,7} }, b.getPawnMoves({ 2,6 })));
		}
		TEST_METHOD(Board_getRookMoves)
		{
			Board b(8, 8);
			Board* bp = &b;
			presetBoard(b, BoardPresets::STANDARD);
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
			presetBoard(b, BoardPresets::STANDARD);
			std::pair<int, int> bishopCoords = { 1, 1 };
			b.setPiece(bishopCoords, std::make_unique<Bishop>(Color::Black));
			auto moves = b.getPiece(bishopCoords)->getValidMoves(bp, bishopCoords);

			Assert::IsTrue(bothStoreSameVals({ {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {2,0} }, moves));
		}
	};
}
