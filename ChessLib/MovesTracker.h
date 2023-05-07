#pragma once
#include "Piece.h"

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

		Move(
			Piece::Type pieceType,
			Piece::Type takenPiece,
			Piece::Color pieceColor,
			std::pair<int, int> from,
			std::pair<int, int> to,
			bool takenPieceMoved
		) : pieceType(pieceType), takenPiece(takenPiece),
			pieceColor(pieceColor), from(from), to(to), takenPieceMoved(takenPieceMoved) {};
	};

	MovesTracker(Board* boardToTrack) : trackedBoard(boardToTrack) {};

	Move getPointedMove() const;

	void addMove(Move const& move);
	void next();
	void previous();
	void revertMove(Move const& move);
	void makeMove(Move const& move);

private:
	std::vector<Move> moves = {};
	Board* trackedBoard = nullptr;
	bool onLatestMove = true;
	int pointedMoveNum = 0;

	std::unique_ptr<Piece> makePieceFromType(Piece::Type type, Piece::Color color);
};

