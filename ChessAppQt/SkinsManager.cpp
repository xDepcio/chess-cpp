#include "SkinsManager.h"
#include "../ChessLib/Piece.h"

std::string SkinsManager::getPathToPiece(Piece* piece) const
{
	if (piece == nullptr)
		return "";

	std::string base = ":/skins/";

	switch (selectedPackage)
	{
	case SkinsManager::SkinsPackage::STANDARD:
		base += "images-standard/";
		break;
	case SkinsManager::SkinsPackage::STARWARS:
		base += "images-star-wars/";
		break;
	default:
		throw std::runtime_error("invalid skins package");
		break;
	}

	switch (piece->getType())
	{
	case Piece::Type::PAWN:
		base += "pawn-";
		break;
	case Piece::Type::BISHOP:
		base += "bishop-";
		break;
	case Piece::Type::KING:
		base += "king-";
		break;
	case Piece::Type::KNIGHT:
		base += "knight-";
		break;
	case Piece::Type::QUEEN:
		base += "queen-";
		break;
	case Piece::Type::ROOK:
		base += "rook-";
		break;
	default:
		throw std::runtime_error("invalid piece type");
		break;
	}

	switch (piece->getColor())
	{
	case Piece::Color::Black:
		base += "black.png";
		break;
	case Piece::Color::White:
		base += "white.png";
		break;
	default:
		throw std::runtime_error("invalid piece color");
		break;
	}

	return base;
}

SkinsManager::SkinsPackage SkinsManager::getSelectedPackage() const
{
    return selectedPackage;
}

void SkinsManager::setSelectedPackage(SkinsPackage const package)
{
    selectedPackage = package;
}
