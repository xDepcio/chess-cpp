// ChessApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../ChessLib/Board.h"
#include "../ChessLib/Piece.h"
#include "../ChessLib/Pawn.h"
#include "../ChessLib/Game.h"
#include <typeinfo>

int main()
{
    //std::cout << "Hello World!\n";
    //Board b(8, 8);
    //b.setPiece({ 0, 0 }, std::make_unique<Pawn>(Piece::Color::White));
    //b.setPiece({ 7, 0 }, std::make_unique<Pawn>(Piece::Color::Black));
    //b.printBoard();
    //b.move({ 0, 0 }, { 1, 0 });
    //b.printBoard();
    Game g;
    g.run();
    //std::vector<Piece*> pieces;
    //pieces.push_back(new Piece(Piece::Color::Black));
    //pieces.push_back(new Pawn(Piece::Color::White));
    //pieces[0]->getName();
    //pieces[1]->getName();
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
