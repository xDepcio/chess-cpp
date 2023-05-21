#pragma once
#include "King.h"
#include "Pawn.h"
#include "Constants.h"

// Tracks board moves and allows checking them step by step
// IDEA: Make Move struct store pointer to taken (if any was taken) piece, then when reverting move just use
//		 this pointer in board.serPiece() method. This way Pieces will preserve their states
//		 like hasMoved, isValidEnpassand etc..
// DONE ^
class MovesTracker
{

public:
	struct Move
	{
		PieceType pieceType;
		PieceType takenPiece;
		std::unique_ptr<Piece> takenPiecePtr;
		Color pieceColor;
		std::pair<int, int> from;
		std::pair<int, int> to;
		bool takenPieceMoved;
		Castle castle;
		std::vector<std::pair<int, int>> affectedSquares;
		EnPassant enPassant;
		bool checkedEnemy;
		Promotions promotion;
		std::unique_ptr<Piece> promotedPawn;

		Move(
			PieceType pieceType,
			PieceType takenPiece,
			std::unique_ptr<Piece> takenPiecePtr,
			Color pieceColor,
			std::pair<int, int> from,
			std::pair<int, int> to,
			bool takenPieceMoved,
			Castle castle = Castle::NONE,
			std::vector<std::pair<int, int>> affectedSquares = {},
			EnPassant enPassant = EnPassant::NONE,
			bool checkedEnemy = false,
			Promotions promotion = Promotions::NONE,
			std::unique_ptr<Piece> promotedPawn = nullptr
		) : pieceType(pieceType), takenPiece(takenPiece), takenPiecePtr(std::move(takenPiecePtr)),
			pieceColor(pieceColor), from(from), to(to), takenPieceMoved(takenPieceMoved),
			castle(castle), affectedSquares(affectedSquares),
			enPassant(enPassant), checkedEnemy(checkedEnemy), promotion(promotion), 
			promotedPawn(std::move(promotedPawn))
		{};
	};

	MovesTracker(Board* boardToTrack) : trackedBoard(boardToTrack) {};

	Move* getPointedMove() const;
	int getPointedMoveIndex() const;

	bool onLatestMove() const;

	void addMove(std::unique_ptr<Move> movePtr);
	void next();
	void previous();
	void revertMove(Move* move);
	void makeMove(Move* move);
	void updateToLatest();
	//std::string toPgn() const;
	//void loadFromPgn(std::string pgnString);
	void saveToFile(const std::string& filePath);

private:
	std::vector<std::unique_ptr<Move>> moves = {};
	Board* trackedBoard = nullptr;
	int pointedMoveNum = -1;

	//std::unique_ptr<Piece> makePieceFromType(Piece::Type type, Piece::Color color);
	std::string coordsToString(std::pair<int, int> const& coords) const;
};

