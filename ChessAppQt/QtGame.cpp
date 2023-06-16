#include "QtGame.h"
#include "../ChessLib/Board.h"
#include "../ChessLib/Pawn.h"
#include "../ChessLib/Knight.h"
#include "../ChessLib/Bishop.h"
#include "../ChessLib/Rook.h"
#include "../ChessLib/King.h"
#include "../ChessLib/Queen.h"
#include "../ChessLib/MovesTracker.h"
#include "../ChessLib/Constants.h"
#include <sstream>
#include <fstream>
#include <ctime>
#include <filesystem>
#include <algorithm>


QtGame::~QtGame()
{
	delete trackedBoard;
}

void QtGame::setupBoard()
{
	Board* boardPt = new Board(constants::BOARD_WIDTH, constants::BOARD_HEIGHT);
	trackedBoard = boardPt;
	boardPt->setPiece({ 1, 0 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 1 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 2 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 3 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 4 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 5 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 6 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 7 }, std::make_unique<Pawn>(Color::Black));

	boardPt->setPiece({ 0, 1 }, std::make_unique<Knight>(Color::Black));
	boardPt->setPiece({ 0, 6 }, std::make_unique<Knight>(Color::Black));

	boardPt->setPiece({ 0, 2 }, std::make_unique<Bishop>(Color::Black));
	boardPt->setPiece({ 0, 5 }, std::make_unique<Bishop>(Color::Black));

	boardPt->setPiece({ 0, 0 }, std::make_unique<Rook>(Color::Black));
	boardPt->setPiece({ 0, 7 }, std::make_unique<Rook>(Color::Black));

	boardPt->setPiece({ 0, 4 }, std::make_unique<King>(Color::Black));

	boardPt->setPiece({ 0, 3 }, std::make_unique<Queen>(Color::Black));


	boardPt->setPiece({ 6, 0 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 1 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 2 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 3 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 4 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 5 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 6 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 7 }, std::make_unique<Pawn>(Color::White));

	boardPt->setPiece({ 7, 1 }, std::make_unique<Knight>(Color::White));
	boardPt->setPiece({ 7, 6 }, std::make_unique<Knight>(Color::White));

	boardPt->setPiece({ 7, 2 }, std::make_unique<Bishop>(Color::White));
	boardPt->setPiece({ 7, 5 }, std::make_unique<Bishop>(Color::White));

	boardPt->setPiece({ 7, 0 }, std::make_unique<Rook>(Color::White));
	boardPt->setPiece({ 7, 7 }, std::make_unique<Rook>(Color::White));

	boardPt->setPiece({ 7, 4 }, std::make_unique<King>(Color::White));

	boardPt->setPiece({ 7, 3 }, std::make_unique<Queen>(Color::White));
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

void QtGame::setBoardState(const BoardState state)
{
	boardState = state;
}

BoardState QtGame::getBoardState() const
{
	return boardState;
}

Color QtGame::getBotColor()
{
	return botColor;
}

void QtGame::setUpBotGame(Color bot_color)
{
	botColor = Color::Black;
	botGame = true;
}

void QtGame::disableBotGame()
{
	botGame = false;
}

bool QtGame::isBotGame()
{
	return botGame;
}

int QtGame::getGameDiff()
{
	return botGameDiff;
}

void QtGame::setGameDiff(int diffLevel)
{
	botGameDiff = diffLevel;
}

void QtGame::choosePromotion(Promotions promotion)
{
	trackedBoard->receivePromotionChoice(promotion);
	trackedBoard->setBoardState(BoardState::PLAYED);
	boardState = trackedBoard->getBoardState();
}

void QtGame::loadGameFromFile(std::string const& filePath)
{
	std::ifstream file(filePath);
	std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, Promotions>> moves;

	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		moves = rawMovesFromString(line);
		file.close();

		trackedBoard->getMovesTracker()->importRaw(moves);
		trackedBoard->setTurn(trackedBoard->getMovesTracker()->getMoveCount() % 2 == 0 ? Color::White : Color::Black);
	}
	else {
		std::cout << "Failed to open the file." << std::endl;
	}
}

void QtGame::saveCurrentGameToFile(std::string const& dirPath)
{
	if (!std::filesystem::exists(constants::SAVE_FILES_DIR))
		std::filesystem::create_directory(constants::SAVE_FILES_DIR);

	std::string movesStr = rawMovesToString(trackedBoard->getMovesTracker()->exportRaw());

	std::time_t currentTime = std::time(nullptr);
	std::string dateString = std::ctime(&currentTime);
	dateString.pop_back();
	std::replace(dateString.begin(), dateString.end(), ':', '.');

	std::ostringstream path;
	path << dirPath << "/" << dateString << ".txt";
	std::ofstream file(path.str(), std::ios::app);

	if (file.is_open())
	{
		file << movesStr;
		file.close();
	}
	else
	{
		std::cerr << "Can't open the file\n";
	}
}

char QtGame::promoToChar(Promotions const& promo) const
{
	switch (promo)
	{
	case Promotions::NONE:
		return ' ';
	case Promotions::BISHOP:
		return 'b';
	case Promotions::KNGIHT:
		return 'k';
	case Promotions::QUEEN:
		return 'q';
	case Promotions::ROOK:
		return 'r';
	}
}

Promotions QtGame::charToPromo(char const& promoChar) const
{
	switch (promoChar)
	{
	case ' ':
		return Promotions::NONE;
	case 'b':
		return Promotions::BISHOP;
	case 'k':
		return Promotions::KNGIHT;
	case 'q':
		return Promotions::QUEEN;
	case 'r':
		return Promotions::ROOK;
	}
}

std::string QtGame::rawMovesToString(std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, Promotions>> rawMoves) const
{
	std::ostringstream ss;

	for (auto& move : rawMoves)
	{
		auto from = move.first.first;
		auto to = move.first.second;

		ss << from.first << from.second << to.first << to.second << promoToChar(move.second);
	}

	return ss.str();
}

std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, Promotions>> QtGame::rawMovesFromString(std::string rawMovesStr) const
{
	std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, Promotions>> moves;

	for (int i = 0; i < rawMovesStr.size(); i+=5)
	{
		moves.push_back({
			{{rawMovesStr[i] - 48, rawMovesStr[i + 1] - 48}, {rawMovesStr[i + 2] - 48, rawMovesStr[i + 3] - 48}}, charToPromo(rawMovesStr[i + 4])
		});
	}

	return moves;
}

std::pair<std::pair<int, int>, std::pair<int, int>> QtGame::parseCoords(std::string coords)
{
	std::pair<int, int> startCoords = { boardCoordinateToInt(coords[1]), boardCoordinateToInt(coords[0]) };
	std::pair<int, int> endCoords = { boardCoordinateToInt(coords[4]), boardCoordinateToInt(coords[3]) };
	return { startCoords, endCoords };
}

int QtGame::boardCoordinateToInt(char coordinateSign) const
{
	if (coordinateSign <= '9') // "9" is 57 in ASCI
	{
		return 7 - (coordinateSign - 49);
	}
	else
	{
		return coordinateSign - 97;
	}
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
	boardState = trackedBoard->getBoardState();
}

Piece* QtGame::getClickedPiece() const
{
	return clickedPiece;
}

std::pair<int, int> QtGame::getClickedPieceCoords() const
{
	return clickedPieceCoords;
}
