#include "Game.h"

void Game::run()
{
	Piece::Color playerTurn = Piece::Color::White;

	Board board(8, 8), *boardPt;
	boardPt = &board;
	boardPt->setPiece({ 1, 0 }, std::make_unique<Pawn>(Piece::Color::Black, 201));
	boardPt->setPiece({ 1, 1 }, std::make_unique<Pawn>(Piece::Color::Black, 202));
	boardPt->setPiece({ 1, 2 }, std::make_unique<Pawn>(Piece::Color::Black, 203));
	boardPt->setPiece({ 1, 3 }, std::make_unique<Pawn>(Piece::Color::Black, 204));
	boardPt->setPiece({ 1, 4 }, std::make_unique<Pawn>(Piece::Color::Black, 205));
	boardPt->setPiece({ 1, 5 }, std::make_unique<Pawn>(Piece::Color::Black, 206));
	boardPt->setPiece({ 1, 6 }, std::make_unique<Pawn>(Piece::Color::Black, 207));
	boardPt->setPiece({ 1, 7 }, std::make_unique<Pawn>(Piece::Color::Black, 208));

	boardPt->setPiece({ 0, 1 }, std::make_unique<Knight>(Piece::Color::Black, 211));
	boardPt->setPiece({ 0, 6 }, std::make_unique<Knight>(Piece::Color::Black, 212));

	boardPt->setPiece({ 0, 2 }, std::make_unique<Bishop>(Piece::Color::Black, 242));
	boardPt->setPiece({ 0, 5 }, std::make_unique<Bishop>(Piece::Color::Black, 242));

	boardPt->setPiece({ 0, 0 }, std::make_unique<Rook>(Piece::Color::Black, 221));
	boardPt->setPiece({ 0, 7 }, std::make_unique<Rook>(Piece::Color::Black, 222));
	
	boardPt->setPiece({ 0, 4 }, std::make_unique<King>(Piece::Color::Black, 231));

	boardPt->setPiece({ 6, 0 }, std::make_unique<Pawn>(Piece::Color::White, 101));
	boardPt->setPiece({ 6, 1 }, std::make_unique<Pawn>(Piece::Color::White, 102));
	boardPt->setPiece({ 6, 2 }, std::make_unique<Pawn>(Piece::Color::White, 103));
	boardPt->setPiece({ 6, 3 }, std::make_unique<Pawn>(Piece::Color::White, 104));
	boardPt->setPiece({ 6, 4 }, std::make_unique<Pawn>(Piece::Color::White, 105));
	boardPt->setPiece({ 6, 5 }, std::make_unique<Pawn>(Piece::Color::White, 106));
	boardPt->setPiece({ 6, 6 }, std::make_unique<Pawn>(Piece::Color::White, 107));
	boardPt->setPiece({ 6, 7 }, std::make_unique<Pawn>(Piece::Color::White, 108));

	boardPt->setPiece({ 7, 1 }, std::make_unique<Knight>(Piece::Color::White, 111));
	boardPt->setPiece({ 7, 6 }, std::make_unique<Knight>(Piece::Color::White, 112));

	boardPt->setPiece({ 7, 2 }, std::make_unique<Bishop>(Piece::Color::White, 142));
	boardPt->setPiece({ 7, 5 }, std::make_unique<Bishop>(Piece::Color::White, 142));

	boardPt->setPiece({ 7, 0 }, std::make_unique<Rook>(Piece::Color::White, 121));
	boardPt->setPiece({ 7, 7 }, std::make_unique<Rook>(Piece::Color::White, 122));

	boardPt->setPiece({ 7, 4 }, std::make_unique<King>(Piece::Color::White, 131));

	std::vector<std::string> messages;
	do
	{
		clearTerminal();
		std::cout << "===============================================\n";
		std::cout << (playerTurn == Piece::Color::White ? "Whites turn" : "Blacks turn") << '\n' << '\n';
		std::cout << "q - quit\n";
		std::cout << "type coordiantes in form (start-end). ex. d2-d4\n";
		//std::cout << "type comma seperated cordinates where start and\ndestination is dot seperated. ex." << " \"1,1.2,1\"\n" << "first coordinate is row and second is column\n";

		std::cout << "===============================================\n";
		boardPt->printBoard();

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
			ss << "Can't move " << (playerTurn == Piece::Color::White ? "Blacks " : "Whites ") << "pieces. Its " << (playerTurn == Piece::Color::White ? "Whites " : "Blacks ") << "turn.";
			messages.push_back(ss.str());
		}
		else
		{
			if (movedPiece->isMoveValid(boardPt, coords.first, coords.second))
			{
				boardPt->move(coords.first, coords.second);
				std::ostringstream ss;
				ss << (playerTurn == Piece::Color::White ? "White" : "Black") << " moved " << movedPiece->getName() << " from " << coords.first.first << ", " << coords.first.second << " to "
					<< coords.second.first << ", " << coords.second.second;
				messages.push_back(ss.str());
				playerTurn = playerTurn == Piece::Color::White ? Piece::Color::Black : Piece::Color::White;
			}
			else
			{
				messages.push_back("Illegal move");
			}
		}

	} while (true);


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
