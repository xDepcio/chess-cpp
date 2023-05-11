#pragma once
//#include "Piece.h"
#include "King.h"

// Tracks board moves and allows checking them step by step
class MovesTracker
{

public:
	struct Move
	{
		Piece::Type pieceType;
		Piece::Type takenPiece;
		Piece::Color pieceColor;
		std::pair<int, int> from;
		std::pair<int, int> to;
		bool takenPieceMoved;
		//King::Castle castle;
		std::vector<std::pair<int, int>> affectedSquares;

		Move(
			Piece::Type pieceType,
			Piece::Type takenPiece,
			Piece::Color pieceColor,
			std::pair<int, int> from,
			std::pair<int, int> to,
			bool takenPieceMoved,
			King::Castle castle = King::Castle::NONE,
			std::vector<std::pair<int, int>> affectedSquares = {}
		) : pieceType(pieceType), takenPiece(takenPiece),
			pieceColor(pieceColor), from(from), to(to), takenPieceMoved(takenPieceMoved),
			//castle(castle), 
			affectedSquares(affectedSquares) {};
	};

	MovesTracker(Board* boardToTrack) : trackedBoard(boardToTrack) {};

	Move getPointedMove() const;
	int getPointedMoveIndex() const;

	bool onLatestMove() const;

	void addMove(Move const& move);
	void next();
	void previous();
	void revertMove(Move const& move);
	void makeMove(Move const& move);
	void updateToLatest();

private:
	std::vector<Move> moves = {};
	Board* trackedBoard = nullptr;
	int pointedMoveNum = -1;

	std::unique_ptr<Piece> makePieceFromType(Piece::Type type, Piece::Color color);
};

