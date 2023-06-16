#pragma once
#include <iostream>

class Piece;

class SkinsManager
{
public:
	enum class SkinsPackage
	{
		STANDARD,
		STARWARS,
		STANDARD_2
	};

	// Returns string in QResource format
	std::string getPathToPiece(Piece* piece) const;
	
	SkinsPackage getSelectedPackage() const;
	void setSelectedPackage(SkinsPackage const package);

private:
	SkinsPackage selectedPackage;
};

