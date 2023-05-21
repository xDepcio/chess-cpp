#pragma once
#include <iostream>
#include <vector>
#include "Constants.h"

class Board;

class Piece
{
public:
	//enum class Color
	//{
	//	White,
	//	Black
	//};

	//enum class Type
	//{
	//	NONE,
	//	PAWN,
	//	KNIGHT,
	//	ROOK,
	//	BISHOP,
	//	KING,
	//	QUEEN
	//};

	Piece(Color withColor) : color(withColor), pieceSignature("x"), debugId(0), type(PieceType::NONE) {};
	Piece(Color withColor, int id) : color(withColor), pieceSignature("x"), debugId(id), type(PieceType::NONE) {};

	bool isMoveValid(Board* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const;

	virtual std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const = 0;

	void gotCaptured(Piece const& captuedBy) {};

	std::string getName() const;

	Color getColor() const;

	void handleGotMoved();

	bool hasMadeFirstMove() const;

	void setMadeFirstMove(bool boolean);

	void handleGotTaken(Piece* takenBy);

	virtual void move(Board* board, std::pair<int, int> to);

	PieceType getType() const;

	Color otherColor() const;

	std::pair<int, int> coords() const;
	void setCoords(std::pair<int, int> newCoords);

protected:
	Color color;
	std::string pieceSignature;
	int debugId;
	bool madeFirstMove = false;
	PieceType type;
	std::pair<int, int> coordinates;
};
