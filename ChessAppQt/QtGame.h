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
	enum class GameState
	{
		CHECKMATED_BLACK,
		CHECKMATED_WHITE,
		STALEMATE,
		PLAYED,
		REQUEST_PROMOTION
	};

	QtGame() : trackedBoard(nullptr), clickedPiece(nullptr), clickedPieceCoords({}) {};
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

	void setGameState(const GameState state);

	GameState getGameState() const;

	void choosePromotion(Promotions promotion);

private:
	Board* trackedBoard;
	Piece* clickedPiece;
	std::pair<int, int> clickedPieceCoords;
	GameState gameState = GameState::PLAYED;
};

