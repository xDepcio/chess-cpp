#pragma once
#include "Piece.h"

class Board;

class Pawn : public Piece
{
private:
	bool validEnPassantLeft = false;
	bool validEnPassantRight = false;

	bool isEnPassantMove(std::pair<int, int> const& move) const;
	void promotionMove(Board* board, std::pair<int, int> const& to);
public:
	//enum class EnPassant
	//{
	//	NONE,
	//	LEFT,
	//	RIGHT
	//};

	Pawn(Color withColor);
	//Pawn(Color withColor, int id);
	//bool isMoveValid(Board* board, std::pair<int, int> const& from, std::pair<int, int> const& to) const override;
	void setValidEnPassantLeft(bool valid);
	void setValidEnPassantRight(bool valid);
	bool canEnPassantLeft() const;
	bool canEnPassantRight() const;

	std::vector<std::pair<int, int>> getValidMoves(Board* board, std::pair<int, int> const& atCoords, bool ignoreCheck = false) const override;
	virtual void move(Board* board, std::pair<int, int> to) override;

	void enPassantMove(Board* board, std::pair<int, int> const& to);
};

