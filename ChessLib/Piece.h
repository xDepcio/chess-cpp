#pragma once
#include <iostream>

class Piece
{
public:
	Piece(int withId) : id(withId) {};

	void printSelf()
	{
		std::cout << id << '\n';
	}

private:
	int id;
};
