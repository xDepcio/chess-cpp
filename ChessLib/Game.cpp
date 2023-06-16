#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "Game.h"
#include "Queen.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "Board.h"
#include "Square.h"


void Game::enableAI(bool enable_ai)
{
	enable_ai ? ai_game = true : ai_game = false;
	return;
}

void Game::setAIcolor(Color color)
{
	human_color = (color == Color::White ? Color::Black : Color::White);
	return;
}

void Game::printBoard(Board* boardPt) const
{
	auto& squares = boardPt->getBoard();

	for (int i = 0; i < squares.size(); i++)
	{
		std::cout << " " << 8 - i << " ";
		for (int j = 0; j < squares[0].size(); j++)
		{
			Piece* squarePiece = squares[i][j].getPiece();
			if (squarePiece != nullptr)
			{
				std::cout << ' ' << squarePiece->getName() << ' ';
			}
			else
			{
				std::cout << " -- ";
			}
		}
		std::cout << '\n';
	}
	std::cout << "    a   b   c   d   e   f   g   h\n";
}

void Game::run()
{
	Color playerTurn = Color::White;

	Board board(8, 8), *boardPt;
	boardPt = &board;


	boardPt->setFenBoard("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKB1R");
	std::cout << "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKB1R\n";

	std::cout << boardPt->getFenBoard() << std::endl;
	return;

	boardPt->setPiece({ 1, 0 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 1 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 2 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 3 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 4 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 5 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 6 }, std::make_unique<Pawn>(Color::Black));
	boardPt->setPiece({ 1, 7 }, std::make_unique<Pawn>(Color::Black));

	boardPt->setPiece({ 0, 1 }, std::make_unique<Knight>(Color::Black));
	boardPt->setPiece({ 0, 6 }, std::make_unique<Knight>(Color::Black));

	boardPt->setPiece({ 0, 2 }, std::make_unique<Bishop>(Color::Black));
	boardPt->setPiece({ 0, 5 }, std::make_unique<Bishop>(Color::Black));

	boardPt->setPiece({ 0, 0 }, std::make_unique<Rook>(Color::Black));
	boardPt->setPiece({ 0, 7 }, std::make_unique<Rook>(Color::Black));
	
	boardPt->setPiece({ 0, 4 }, std::make_unique<King>(Color::Black));

	boardPt->setPiece({ 0, 3 }, std::make_unique<Queen>(Color::Black));


	boardPt->setPiece({ 6, 0 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 1 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 2 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 3 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 4 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 5 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 6 }, std::make_unique<Pawn>(Color::White));
	boardPt->setPiece({ 6, 7 }, std::make_unique<Pawn>(Color::White));

	boardPt->setPiece({ 7, 1 }, std::make_unique<Knight>(Color::White));
	boardPt->setPiece({ 7, 6 }, std::make_unique<Knight>(Color::White));

	boardPt->setPiece({ 7, 2 }, std::make_unique<Bishop>(Color::White));
	boardPt->setPiece({ 7, 5 }, std::make_unique<Bishop>(Color::White));

	boardPt->setPiece({ 7, 0 }, std::make_unique<Rook>(Color::White));
	boardPt->setPiece({ 7, 7 }, std::make_unique<Rook>(Color::White));

	boardPt->setPiece({ 7, 4 }, std::make_unique<King>(Color::White));

	boardPt->setPiece({ 7, 3 }, std::make_unique<Queen>(Color::White));

	//std::cout << boardPt->getFenBoard() << std::endl;
	



	std::vector<std::string> messages;
	if (not ai_game)
	{
		do
		{
			clearTerminal();
			std::cout << boardPt->getFenBoard() << std::endl;
			std::cout << "===============================================\n";
			std::cout << (playerTurn == Color::White ? "Whites turn" : "Blacks turn") << '\n' << '\n';
			std::cout << "q - quit\n";
			std::cout << "type coordiantes in form (start-end). ex. d2-d4\n";
			//std::cout << "type comma seperated cordinates where start and\ndestination is dot seperated. ex." << " \"1,1.2,1\"\n" << "first coordinate is row and second is column\n";

			std::cout << "===============================================\n";
			printBoard(boardPt);

			for (auto& msg : messages)
			{
				std::cout << msg << '\n';
			}
			std::cout << '\n';
			messages = {};

			std::cout << "Your input: ";
			std::string input;
			std::cin >> input;
			std::cout << input << '\n';
			auto coords = parseCoords(input);

			Piece* movedPiece = boardPt->getPiece(coords.first);

			if (movedPiece == nullptr)
			{
				messages.push_back("Illegal move");
			}
			else if (movedPiece->getColor() != playerTurn)
			{
				std::ostringstream ss;
				ss << "Can't move " << (playerTurn == Color::White ? "Blacks " : "Whites ") << "pieces. Its " << (playerTurn == Color::White ? "Whites " : "Blacks ") << "turn.";
				messages.push_back(ss.str());
			}
			else
			{
				if (movedPiece->isMoveValid(boardPt, coords.first, coords.second))
				{
					boardPt->move(coords.first, coords.second);
					std::ostringstream ss;
					ss << (playerTurn == Color::White ? "White" : "Black") << " moved " << movedPiece->getName() << " from " << coords.first.first << ", " << coords.first.second << " to "
						<< coords.second.first << ", " << coords.second.second;
					messages.push_back(ss.str());
					playerTurn = playerTurn == Color::White ? Color::Black : Color::White;
					boardPt->setTurn(playerTurn);
				}
				else
				{
					messages.push_back("Illegal move");
				}
			}

		} while (true);
	}
	/// Ai Game
	else
	{

		do
		{
			clearTerminal();
			std::cout << "===============================================\n";
			std::cout << (playerTurn == Color::White ? "Whites turn" : "Blacks turn") << '\n' << '\n';
			std::cout << "q - quit\n";
			std::cout << "type coordiantes in form (start-end). ex. d2-d4\n";
			//std::cout << "type comma seperated cordinates where start and\ndestination is dot seperated. ex." << " \"1,1.2,1\"\n" << "first coordinate is row and second is column\n";

			std::cout << "===============================================\n";
			printBoard(boardPt);

			for (auto& msg : messages)
			{
				std::cout << msg << '\n';
			}
			std::cout << '\n';
			messages = {};

			// Human Turn
			if (playerTurn == human_color)
			{
				std::cout << "Your input: ";
				std::string input;
				std::cin >> input;
				std::cout << input << '\n';
				auto coords = parseCoords(input);

				Piece* movedPiece = boardPt->getPiece(coords.first);

				if (movedPiece == nullptr)
				{
					messages.push_back("Illegal move");
				}
				else if (movedPiece->getColor() != playerTurn)
				{
					std::ostringstream ss;
					ss << "Can't move " << (playerTurn == Color::White ? "Blacks " : "Whites ") << "pieces. Its " << (playerTurn == Color::White ? "Whites " : "Blacks ") << "turn.";
					messages.push_back(ss.str());
				}
				else
				{
					if (movedPiece->isMoveValid(boardPt, coords.first, coords.second))
					{
						boardPt->move(coords.first, coords.second);
						std::ostringstream ss;
						ss << (playerTurn == Color::White ? "White" : "Black") << " moved " << movedPiece->getName() << " from " << coords.first.first << ", " << coords.first.second << " to "
							<< coords.second.first << ", " << coords.second.second;
						messages.push_back(ss.str());
						playerTurn = playerTurn == Color::White ? Color::Black : Color::White;
						boardPt->setTurn(playerTurn);
					}
					else
					{
						messages.push_back("Illegal move");
					}
				}
			}
			// Computer Move
			else
			{
				//std::string input = chessinator3000.getBestMove(boardPt->getFenBoard());
				std::string  input = "d2-d3";
				
				auto coords = parseCoords(input);

				Piece* movedPiece = boardPt->getPiece(coords.first);

				if (movedPiece == nullptr)
				{
					messages.push_back("Illegal move");
				}
				else if (movedPiece->getColor() != playerTurn)
				{
					std::ostringstream ss;
					ss << "Can't move " << (playerTurn == Color::White ? "Blacks " : "Whites ") << "pieces. Its " << (playerTurn == Color::White ? "Whites " : "Blacks ") << "turn.";
					messages.push_back(ss.str());
				}
				else
				{
					if (movedPiece->isMoveValid(boardPt, coords.first, coords.second))
					{
						boardPt->move(coords.first, coords.second);
						std::ostringstream ss;
						ss << (playerTurn == Color::White ? "White" : "Black") << " moved " << movedPiece->getName() << " from " << coords.first.first << ", " << coords.first.second << " to "
							<< coords.second.first << ", " << coords.second.second;
						messages.push_back(ss.str());
						playerTurn = playerTurn == Color::White ? Color::Black : Color::White;
						boardPt->setTurn(playerTurn);
					}
					else
					{
						messages.push_back("Illegal move");
					}
				}
			}

		} while (true);
	}


}

void Game::clearTerminal()
{
	std::cout << "\x1B[2J\x1B[3J\x1B[H";
}

//std::pair<std::pair<int, int>, std::pair<int, int>> Game::parseCoords(std::string coords)
//{
//	bool filledFirst = false;
//	std::pair<int, int> startCoords;
//	std::pair<int, int> endCoords;
//	for (int i = 0; i < coords.size(); i++)
//	{
//		char delim = coords[i];
//		if (delim == '.')
//		{
//			filledFirst = true;
//		}
//		if (delim == ',')
//		{
//			if (!filledFirst)
//			{
//				int numRow = coords[i - 1] - 48;
//				int numCol = coords[i + 1] - 48;
//				startCoords.first = numRow;
//				startCoords.second = numCol;
//
//			}
//			else
//			{
//				int numRow = coords[i - 1] - 48;
//				int numCol = coords[i + 1] - 48;
//				endCoords.first = numRow;
//				endCoords.second = numCol;
//
//			}
//		}
//	}
//	return std::pair<std::pair<int, int>, std::pair<int, int>>(startCoords, endCoords);
//}

std::pair<std::pair<int, int>, std::pair<int, int>> Game::parseCoords(std::string coords)
{
	std::pair<int, int> startCoords = { boardCoordinateToInt(coords[1]), boardCoordinateToInt(coords[0]) };
	std::pair<int, int> endCoords = { boardCoordinateToInt(coords[4]), boardCoordinateToInt(coords[3]) };
	return { startCoords, endCoords };
}

int Game::boardCoordinateToInt(char coordinateSign) const
{
	if (coordinateSign <= 57) // "9" is 57 in ASCI
	{
		return 7 - (coordinateSign - 49);
	}
	else
	{
		return coordinateSign - 97;
	}
}
