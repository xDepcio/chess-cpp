#pragma once
#include "Piece.h"
#include "Metadata.h"

using namespace metadata;

class Pawn : public Piece
{
public:
	Pawn(Color color) : Piece(color) {};
};

