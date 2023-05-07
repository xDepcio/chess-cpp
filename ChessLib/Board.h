#pragma once
#include "Piece.h"
#include "Square.h"
#include "Pawn.h"
#include "King.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"

class Board
{
public:

	Board(int width, int height);

	std::unique_ptr<Piece> setPiece(std::pair<int, int> cords, std::unique_ptr<Piece> piece);

	std::vector<std::vector<Square> >& getBoard();

	void printBoard() const;

	Piece* getPiece(std::pair<int, int> coords) const;

	std::pair<int, int> getKingLocation(Piece::Color const kingColor) const;

	std::vector<std::pair<int, int>> getPawnMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getKingMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getKnightMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getHorizontalMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getVerticalMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);

	std::vector<std::pair<int, int>> getDiagonalMoves(std::pair<int, int> atCoords, bool ignoreCheck);

	void move(std::pair<int, int> from, std::pair<int, int> to);

	bool isCheck(Piece::Color const piecesColor);

	bool isCheckMate(Piece::Color const piecesColor);

	bool isStalemate(Piece::Color const piecesColor);

	bool areCoordinatesValid(std::pair<int, int> coordinates) const;

protected:
	int width;
	int height;
	std::vector<std::vector<Square> > squares = { };

	struct moveState
	{
		enum class Status {
			valid,
			invalid
		};
		enum class Reason
		{
			valid_empty,
			valid_takes_enemy,
			invalid_takes_own,
			invalid_causes_own_check,
			invalid_wrong_coords
		};
		Status status;
		Reason reason;
	};

	moveState addMoveIfValid(std::pair<int, int>& from, std::pair<int, int> to, std::vector<std::pair<int, int>>& addTo, bool ignoreCheck = false);
};
