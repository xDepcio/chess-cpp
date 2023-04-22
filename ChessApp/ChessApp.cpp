// ChessApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../ChessLib/Board.h"
#include "../ChessLib/Pawn.h"
#include "../ChessLib/Metadata.h"
#include "../ChessLib/Piece.h"

using namespace metadata;

int main()
{
    std::cout << "Hello World!\n";
    Board b;

    b.setPiece(Pawn(Color::Black), { 0, 1 });
    b.setPiece(Pawn(Color::Black), { 1, 1 });
    b.setPiece(Pawn(Color::Black), { 2, 1 });
    b.setPiece(Pawn(Color::Black), { 3, 1 });
    
    b.setPiece(Pawn(Color::White), { 0, 6 });
    b.setPiece(Pawn(Color::White), { 1, 6 });
    b.setPiece(Pawn(Color::White), { 2, 6 });
    b.setPiece(Pawn(Color::White), { 3, 6 });
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
