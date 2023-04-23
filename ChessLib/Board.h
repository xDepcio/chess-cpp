#pragma once
#include "Piece.h"
#include "Square.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Pawn.h"

class Board
{
public:
	Board(int width, int height);

	std::unique_ptr<Piece> setPiece(std::pair<int, int> cords, std::unique_ptr<Piece> piece);

	std::vector<std::vector<Square> >& getBoard();

	void printBoard() const;
	Piece* getPiece(std::pair<int, int> coords) const;

	std::vector<std::pair<int, int>> getPawnMoves(std::pair<int, int> atCoords);
	std::vector<std::pair<int, int>>& getKnightMoves(std::pair<int, int> atCoords) const;
	std::vector<std::pair<int, int>>& getHorizontalMoves(std::pair<int, int> atCoords) const;
	std::vector<std::pair<int, int>>& getVerticalMoves(std::pair<int, int> atCoords) const;
	std::vector<std::pair<int, int>>& getKingMoves(std::pair<int, int> atCoords) const;

	void move(std::pair<int, int> from, std::pair<int, int> to);

	bool areCoordinatesValid(std::pair<int, int> coordinates) const;

private:
	int width;
	int height;
	std::vector<std::vector<Square> > squares = { };
};
