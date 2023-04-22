// ChessApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "../ChessLib/Board.h"
//#include "../ChessLib/Pawn.h"
//#include "../ChessLib/Metadata.h"
//#include "../ChessLib/Piece.h"

//using namespace metadata;

class Piece
{
public:
    Piece() : id(0) {};
    Piece(int withId) : id(withId) {};

    int getId()
    {
        return id;
    }

private:
    int id;
};

class Square
{
private:
    std::unique_ptr<Piece> piece;
public:
    Square() : piece(nullptr) {};
    //Square(std::unique_ptr<Piece> ptr) : piece(std::move(ptr)) {};

    Piece* getPiece()
    {
        return piece.get();
    }

    void setPiece(Piece& piece)
    {
        this->piece = std::move(std::make_unique<Piece>(piece));
    }

};

class Board
{
public:
    Board() {};

    void setPiece(Square& square, Piece& piece)
    {
        square.setPiece(piece);
    }

private:

};



int main()
{
    std::cout << "Hello World!\n";
    //Board b;

    //b.setPiece(Pawn(Color::Black), { 0, 1 });
    //b.setPiece(Pawn(Color::Black), { 1, 1 });
    //b.setPiece(Pawn(Color::Black), { 2, 1 });
    //b.setPiece(Pawn(Color::Black), { 3, 1 });
    //
    //b.setPiece(Pawn(Color::White), { 0, 6 });
    //b.setPiece(Pawn(Color::White), { 1, 6 });
    //b.setPiece(Pawn(Color::White), { 2, 6 });
    //b.setPiece(Pawn(Color::White), { 3, 6 });
    Piece p1(1);
    Piece p2(2);
    Piece p3(3);

    //Square s1(std::move(p1));
    //Square s2(std::move(p2));
    //Square s3(std::move(p3));
    Square s1;
    Square s2;
    Square s3;
    Board b;
    b.setPiece(s1, p1);
    b.setPiece(s2, p2);
    b.setPiece(s3, p3);
    //s1.setPiece(p1);
    //s2.setPiece(p2);
    //s3.setPiece(p3);
    
    std::cout << s1.getPiece()->getId() << '\n';
    std::cout << s2.getPiece()->getId() << '\n';
    std::cout << s3.getPiece()->getId() << '\n';

    //Board b;
    //b.setPiece(s1, std::move(p2));

    //s1.setPiece(std::move(p2));

    std::cout << s1.getPiece()->getId() << '\n';
    std::cout << s2.getPiece()->getId() << '\n';
    std::cout << s3.getPiece()->getId() << '\n';

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
