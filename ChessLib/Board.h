#pragma once
#include "Piece.h"
#include <vector>
#include <iostream>
#include <typeinfo>
#include "Constants.h"

class MovesTracker;
class Queen;
class Bishop;
class Rook;
class Knight;
class King;
class Pawn;
class Square;

class Board
{
public:
	enum class BoardState
	{
		CHECKMATED_WHITE,
		CHECKMATED_BLACK,
		STALEMATE,
		PLAYED,
		REQUEST_PROMOTION
	};
	//enum class Promotions
	//{
	//	ROOK,
	//	QUEEN,
	//	KNIGHT,
	//	BISHOP
	//};

	Board(int width, int height);
	~Board();

	std::unique_ptr<Piece> setPiece(std::pair<int, int> cords, std::unique_ptr<Piece> piece);

	std::vector<std::vector<Square> >& getBoard();

	void printBoard() const;

	Piece* getPiece(std::pair<int, int> coords) const;
	std::unique_ptr<Piece> getPieceUniquePtr(const std::pair<int, int>& pieceCoords);

	std::pair<int, int> getKingLocation(Piece::Color const kingColor) const;

	std::vector<std::pair<int, int>> getPawnMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getKingMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getKnightMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getHorizontalMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getVerticalMoves(std::pair<int, int> atCoords, bool ignoreCheck = false);
	std::vector<std::pair<int, int>> getCastleMoves(Piece::Color kingColor);
	std::vector<std::pair<int, int>> getEnPassantMoves(std::pair<int, int> pawnCoords);


	std::vector<std::pair<int, int>> getDiagonalMoves(std::pair<int, int> atCoords, bool ignoreCheck);

	void move(std::pair<int, int> from, std::pair<int, int> to);

	bool isCheck(Piece::Color const piecesColor);

	bool isCheckMate(Piece::Color const piecesColor);

	bool isStalemate(Piece::Color const piecesColor);

	bool areCoordinatesValid(std::pair<int, int> coordinates) const;

	MovesTracker* getMovesTracker() const;

	Piece::Color getTurn() const;

	void setTurn(Piece::Color const turnColor);

	void invalidateEnPassantesOnNextMove();

	void setBoardState(BoardState stateToSet);

	BoardState getBoardState() const;

	void requestPromotionChoice(std::pair<int, int> const& moveFrom, std::pair<int, int> const& moveTo);
	void receivePromotionChoice(Promotions promotion);

protected:
	int width;
	int height;
	std::vector<std::vector<Square> > squares = { };
	MovesTracker* movesTracker;
	Piece::Color turn = Piece::Color::White;
	bool shouldInvalidateEnPassantes = false;
	BoardState boardState = BoardState::PLAYED;
	std::pair<int, int> promoMoveFrom;
	std::pair<int, int> promoMoveTo;

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

	moveState addMoveIfValid(std::pair<int, int> from, std::pair<int, int> to, std::vector<std::pair<int, int>>& addTo, bool ignoreCheck = false);
	void invalidateEnPassantes(Piece::Color piecesColorToInvalidate);
};
