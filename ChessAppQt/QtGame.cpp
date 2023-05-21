#include "QtGame.h"
#include "../../Chess/ChessLib/Board.h"
#include "../../Chess/ChessLib/Pawn.h"
#include "../../Chess/ChessLib/Knight.h"
#include "../../Chess/ChessLib/Bishop.h"
#include "../../Chess/ChessLib/Rook.h"
#include "../../Chess/ChessLib/King.h"
#include "../../Chess/ChessLib/Queen.h"

QtGame::~QtGame()
{
	delete trackedBoard;
}

void QtGame::setupBoard()
{
	Board* boardPt = new Board(8, 8);
	//Board board(8, 8), *boardPt;
	//boardPt = &board;
	trackedBoard = boardPt;
	boardPt->setPiece({ 1, 0 }, std::make_unique<Pawn>(Color::Black, 201));
	boardPt->setPiece({ 1, 1 }, std::make_unique<Pawn>(Color::Black, 202));
	boardPt->setPiece({ 1, 2 }, std::make_unique<Pawn>(Color::Black, 203));
	boardPt->setPiece({ 1, 3 }, std::make_unique<Pawn>(Color::Black, 204));
	boardPt->setPiece({ 1, 4 }, std::make_unique<Pawn>(Color::Black, 205));
	boardPt->setPiece({ 1, 5 }, std::make_unique<Pawn>(Color::Black, 206));
	boardPt->setPiece({ 1, 6 }, std::make_unique<Pawn>(Color::Black, 207));
	boardPt->setPiece({ 1, 7 }, std::make_unique<Pawn>(Color::Black, 208));

	boardPt->setPiece({ 0, 1 }, std::make_unique<Knight>(Color::Black, 211));
	boardPt->setPiece({ 0, 6 }, std::make_unique<Knight>(Color::Black, 212));

	boardPt->setPiece({ 0, 2 }, std::make_unique<Bishop>(Color::Black, 242));
	boardPt->setPiece({ 0, 5 }, std::make_unique<Bishop>(Color::Black, 242));

	boardPt->setPiece({ 0, 0 }, std::make_unique<Rook>(Color::Black, 221));
	boardPt->setPiece({ 0, 7 }, std::make_unique<Rook>(Color::Black, 222));

	boardPt->setPiece({ 0, 4 }, std::make_unique<King>(Color::Black, 231));

	boardPt->setPiece({ 0, 3 }, std::make_unique<Queen>(Color::Black, 251));


	boardPt->setPiece({ 6, 0 }, std::make_unique<Pawn>(Color::White, 101));
	boardPt->setPiece({ 6, 1 }, std::make_unique<Pawn>(Color::White, 102));
	boardPt->setPiece({ 6, 2 }, std::make_unique<Pawn>(Color::White, 103));
	boardPt->setPiece({ 6, 3 }, std::make_unique<Pawn>(Color::White, 104));
	boardPt->setPiece({ 6, 4 }, std::make_unique<Pawn>(Color::White, 105));
	boardPt->setPiece({ 6, 5 }, std::make_unique<Pawn>(Color::White, 106));
	boardPt->setPiece({ 6, 6 }, std::make_unique<Pawn>(Color::White, 107));
	boardPt->setPiece({ 6, 7 }, std::make_unique<Pawn>(Color::White, 108));

	boardPt->setPiece({ 7, 1 }, std::make_unique<Knight>(Color::White, 111));
	boardPt->setPiece({ 7, 6 }, std::make_unique<Knight>(Color::White, 112));

	boardPt->setPiece({ 7, 2 }, std::make_unique<Bishop>(Color::White, 142));
	boardPt->setPiece({ 7, 5 }, std::make_unique<Bishop>(Color::White, 142));

	boardPt->setPiece({ 7, 0 }, std::make_unique<Rook>(Color::White, 121));
	boardPt->setPiece({ 7, 7 }, std::make_unique<Rook>(Color::White, 122));

	boardPt->setPiece({ 7, 4 }, std::make_unique<King>(Color::White, 131));

	boardPt->setPiece({ 7, 3 }, std::make_unique<Queen>(Color::White, 151));

	//lastBoardState = boardPt->getBoard();
}

void QtGame::run()
{
	setupBoard();
}

Piece* QtGame::getPieceAtCoords(std::pair<int, int> const& coords) const
{
	return trackedBoard->getPiece(coords);
}

Board* QtGame::getBoard() const
{
	return trackedBoard;
}

void QtGame::setGameState(const GameState state)
{
	gameState = state;
}

QtGame::GameState QtGame::getGameState() const
{
	return gameState;
}

void QtGame::choosePromotion(Promotions promotion)
{
	trackedBoard->receivePromotionChoice(promotion);
	gameState = GameState::PLAYED;
}

std::vector<std::vector<Square>>& QtGame::getSquares()
{
	return trackedBoard->getBoard();
}

void QtGame::setClickedPiece(Piece* piece)
{
	clickedPiece = piece;
}

void QtGame::setClickedPieceCoords(std::pair<int, int> const& coords)
{
	clickedPieceCoords = coords;
}

bool QtGame::isMoveValid(std::pair<int, int> const& from, std::pair<int, int> const& to)
{
	return trackedBoard->getPiece(from)->isMoveValid(trackedBoard, from, to);
}

void QtGame::move(Piece* piece, std::pair<int, int> const& to)
{
	piece->move(trackedBoard, to);
	switch (trackedBoard->getBoardState())
	{
	case BoardState::STALEMATE:
		gameState = GameState::STALEMATE;
		break;
	case BoardState::CHECKMATED_BLACK:
		gameState = GameState::CHECKMATED_BLACK;
		break;
	case BoardState::CHECKMATED_WHITE:
		gameState = GameState::CHECKMATED_WHITE;
		break;
	case BoardState::REQUEST_PROMOTION:
		gameState = GameState::REQUEST_PROMOTION;
		break;
	case BoardState::PLAYED:
		gameState = GameState::PLAYED;
		break;
	default:
		break;
	}
}

Piece* QtGame::getClickedPiece() const
{
	return clickedPiece;
}

std::pair<int, int> QtGame::getClickedPieceCoords() const
{
	return clickedPieceCoords;
}
