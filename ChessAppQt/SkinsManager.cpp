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
	case SkinsPackage::STANDARD_2:
		base += "images-standard-2/";
		break;
	default:
		throw std::runtime_error("invalid skins package");
		break;
	}

	switch (piece->getType())
	{
	case PieceType::PAWN:
		base += "pawn-";
		break;
	case PieceType::BISHOP:
		base += "bishop-";
		break;
	case PieceType::KING:
		base += "king-";
		break;
	case PieceType::KNIGHT:
		base += "knight-";
		break;
	case PieceType::QUEEN:
		base += "queen-";
		break;
	case PieceType::ROOK:
		base += "rook-";
		break;
	default:
		throw std::runtime_error("invalid piece type");
		break;
	}

	switch (piece->getColor())
	{
	case Color::Black:
		base += "black.png";
		break;
	case Color::White:
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
