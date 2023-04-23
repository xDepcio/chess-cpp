#pragma once
#include "Piece.h"
#include "Square.h"
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

	std::vector<std::pair<int, int>>& getPawnMoves(std::pair<int, int> atCoords) const;
	std::vector<std::pair<int, int>>& getKnightMoves(std::pair<int, int> atCoords) const;
	std::vector<std::pair<int, int>>& getHorizontalMoves(std::pair<int, int> atCoords) const;
	std::vector<std::pair<int, int>>& getVerticalMoves(std::pair<int, int> atCoords) const;
	std::vector<std::pair<int, int>>& getKingMoves(std::pair<int, int> atCoords) const;

	void move(std::pair<int, int> from, std::pair<int, int> to);

private:
	std::vector<std::vector<Square> > squares = { };
};
