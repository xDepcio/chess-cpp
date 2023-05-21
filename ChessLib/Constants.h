#pragma once
enum class Promotions
{
	ROOK,
	QUEEN,
	KNGIHT,
	BISHOP,
	NONE
};

enum class BoardState
{
	CHECKMATED_WHITE,
	CHECKMATED_BLACK,
	STALEMATE,
	PLAYED,
	REQUEST_PROMOTION
};

enum class Castle
{
	NONE,
	LONG,
	SHORT
};

enum class EnPassant
{
	NONE,
	LEFT,
	RIGHT
};

enum class Color
{
	White,
	Black
};

enum class PieceType
{
	NONE,
	PAWN,
	KNIGHT,
	ROOK,
	BISHOP,
	KING,
	QUEEN
};