#include "QtGame.h"

void QtGame::setupBoard()
{
	Board* boardPt = new Board(8, 8);
	//Board board(8, 8), *boardPt;
	//boardPt = &board;
	trackedBoard = boardPt;
	boardPt->setPiece({ 1, 0 }, std::make_unique<Pawn>(Piece::Color::Black, 201));
	boardPt->setPiece({ 1, 1 }, std::make_unique<Pawn>(Piece::Color::Black, 202));
	boardPt->setPiece({ 1, 2 }, std::make_unique<Pawn>(Piece::Color::Black, 203));
	boardPt->setPiece({ 1, 3 }, std::make_unique<Pawn>(Piece::Color::Black, 204));
	boardPt->setPiece({ 1, 4 }, std::make_unique<Pawn>(Piece::Color::Black, 205));
	boardPt->setPiece({ 1, 5 }, std::make_unique<Pawn>(Piece::Color::Black, 206));
	boardPt->setPiece({ 1, 6 }, std::make_unique<Pawn>(Piece::Color::Black, 207));
	boardPt->setPiece({ 1, 7 }, std::make_unique<Pawn>(Piece::Color::Black, 208));

	boardPt->setPiece({ 0, 1 }, std::make_unique<Knight>(Piece::Color::Black, 211));
	boardPt->setPiece({ 0, 6 }, std::make_unique<Knight>(Piece::Color::Black, 212));

	boardPt->setPiece({ 0, 2 }, std::make_unique<Bishop>(Piece::Color::Black, 242));
	boardPt->setPiece({ 0, 5 }, std::make_unique<Bishop>(Piece::Color::Black, 242));

	boardPt->setPiece({ 0, 0 }, std::make_unique<Rook>(Piece::Color::Black, 221));
	boardPt->setPiece({ 0, 7 }, std::make_unique<Rook>(Piece::Color::Black, 222));

	boardPt->setPiece({ 0, 4 }, std::make_unique<King>(Piece::Color::Black, 231));

	boardPt->setPiece({ 0, 3 }, std::make_unique<Queen>(Piece::Color::Black, 251));


	boardPt->setPiece({ 6, 0 }, std::make_unique<Pawn>(Piece::Color::White, 101));
	boardPt->setPiece({ 6, 1 }, std::make_unique<Pawn>(Piece::Color::White, 102));
	boardPt->setPiece({ 6, 2 }, std::make_unique<Pawn>(Piece::Color::White, 103));
	boardPt->setPiece({ 6, 3 }, std::make_unique<Pawn>(Piece::Color::White, 104));
	boardPt->setPiece({ 6, 4 }, std::make_unique<Pawn>(Piece::Color::White, 105));
	boardPt->setPiece({ 6, 5 }, std::make_unique<Pawn>(Piece::Color::White, 106));
	boardPt->setPiece({ 6, 6 }, std::make_unique<Pawn>(Piece::Color::White, 107));
	boardPt->setPiece({ 6, 7 }, std::make_unique<Pawn>(Piece::Color::White, 108));

	boardPt->setPiece({ 7, 1 }, std::make_unique<Knight>(Piece::Color::White, 111));
	boardPt->setPiece({ 7, 6 }, std::make_unique<Knight>(Piece::Color::White, 112));

	boardPt->setPiece({ 7, 2 }, std::make_unique<Bishop>(Piece::Color::White, 142));
	boardPt->setPiece({ 7, 5 }, std::make_unique<Bishop>(Piece::Color::White, 142));

	boardPt->setPiece({ 7, 0 }, std::make_unique<Rook>(Piece::Color::White, 121));
	boardPt->setPiece({ 7, 7 }, std::make_unique<Rook>(Piece::Color::White, 122));

	boardPt->setPiece({ 7, 4 }, std::make_unique<King>(Piece::Color::White, 131));

	boardPt->setPiece({ 7, 3 }, std::make_unique<Queen>(Piece::Color::White, 151));
}

void QtGame::run()
{
	setupBoard();
}

std::vector<std::vector<Square>>& QtGame::getBoard()
{
	return trackedBoard->getBoard();
}
