#pragma once
#include <iostream>
#include <vector>
#include "../ChessLib/Constants.h"

class Piece;
class Board;
class Square;

class QtGame
{
public:

	QtGame() : trackedBoard(nullptr), clickedPiece(nullptr), clickedPieceCoords({}), botColor(Color::Black) {};
	~QtGame();

	void setupBoard();
	void run();

	Piece* getPieceAtCoords(std::pair<int, int> const& coords) const;
	
	std::vector<std::vector<Square> >& getSquares();

	bool isMoveValid(std::pair<int, int> const& from, std::pair<int, int> const& to);

	void move(Piece* piece, std::pair<int, int> const& to);

	void setClickedPiece(Piece* piece);
	void setClickedPieceCoords(std::pair<int, int> const& coords);

	Piece* getClickedPiece() const;
	std::pair<int, int> getClickedPieceCoords() const;

	Board* getBoard() const;

	void setBoardState(const BoardState state);

	BoardState getBoardState() const;

	Color getBotColor();

	void setUpBotGame(Color bot_color);

	void disableBotGame();

	bool isBotGame();

	void choosePromotion(Promotions promotion);

	void loadGameFromFile(std::string const& filePath);

	void saveCurrentGameToFile(std::string const& dirPath);

	std::string rawMovesToString(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> rawMoves) const;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> rawMovesFromString(std::string rawMovesStr) const;

	std::pair<std::pair<int, int>, std::pair<int, int>> parseCoords(std::string coords);
	int boardCoordinateToInt(char coordinateSign) const;


private:
	bool botGame = false;
	Color botColor;
	Board* trackedBoard;
	Piece* clickedPiece;
	std::pair<int, int> clickedPieceCoords;
	BoardState boardState = BoardState::PLAYED;
};

