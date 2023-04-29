#pragma once
#include "Piece.h"
#include "Square.h"
#include "Pawn.h"
#include "King.h"
#include <vector>
#include <iostream>
#include <typeinfo>

class Board
{
public:
	Board(int width, int height);

	std::unique_ptr<Piece> setPiece(std::pair<int, int> cords, std::unique_ptr<Piece> piece);

	std::vector<std::vector<Square> >& getBoard();

	void printBoard() const;

	Piece* getPiece(std::pair<int, int> coords) const;

	//King* getKing(Piece::Color const kingColor) const;
	std::pair<int, int> getKingLocation(Piece::Color const kingColor) const;

	std::vector<std::pair<int, int>> getPawnMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getKingMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getKnightMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getHorizontalMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getVerticalMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);

	void move(std::pair<int, int> from, std::pair<int, int> to);

	bool isCheck(Piece::Color const piecesColor) const;

	bool areCoordinatesValid(std::pair<int, int> coordinates) const;

private:
	int width;
	int height;
	std::vector<std::vector<Square> > squares = { };
};
