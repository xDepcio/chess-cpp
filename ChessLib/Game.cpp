#include "Game.h"

void Game::run()
{
	Piece::Color playerTurn = Piece::Color::White;

	Board board(8, 8), *boardPt;
	boardPt = &board;
	boardPt->setPiece({ 1, 0 }, std::make_unique<Pawn>(Piece::Color::Black, 1));
	boardPt->setPiece({ 1, 1 }, std::make_unique<Pawn>(Piece::Color::Black, 2));
	boardPt->setPiece({ 1, 2 }, std::make_unique<Pawn>(Piece::Color::Black, 3));
	boardPt->setPiece({ 1, 3 }, std::make_unique<Pawn>(Piece::Color::Black, 4));
	boardPt->setPiece({ 1, 4 }, std::make_unique<Pawn>(Piece::Color::Black, 5));
	boardPt->setPiece({ 1, 5 }, std::make_unique<Pawn>(Piece::Color::Black, 6));
	boardPt->setPiece({ 1, 6 }, std::make_unique<Pawn>(Piece::Color::Black, 7));
	boardPt->setPiece({ 1, 7 }, std::make_unique<Pawn>(Piece::Color::Black, 8));

	boardPt->setPiece({ 6, 0 }, std::make_unique<Pawn>(Piece::Color::White, 9));
	boardPt->setPiece({ 6, 1 }, std::make_unique<Pawn>(Piece::Color::White, 10));
	boardPt->setPiece({ 6, 2 }, std::make_unique<Pawn>(Piece::Color::White, 11));
	boardPt->setPiece({ 6, 3 }, std::make_unique<Pawn>(Piece::Color::White, 12));
	boardPt->setPiece({ 6, 4 }, std::make_unique<Pawn>(Piece::Color::White, 13));
	boardPt->setPiece({ 6, 5 }, std::make_unique<Pawn>(Piece::Color::White, 14));
	boardPt->setPiece({ 6, 6 }, std::make_unique<Pawn>(Piece::Color::White, 15));
	boardPt->setPiece({ 6, 7 }, std::make_unique<Pawn>(Piece::Color::White, 16));

	boardPt->setPiece({ 2, 1 }, std::make_unique<Pawn>(Piece::Color::White, 17));

	std::vector<std::string> messages;
	do
	{
		clearTerminal();
		std::cout << "===============================================\n";
		std::cout << (playerTurn == Piece::Color::White ? "Whites turn" : "Blacks turn") << '\n' << '\n';
		std::cout << "q - quit\n";
		std::cout << "type comma seperated cordinates where start and\ndestination is dot seperated. ex." << " \"1,1.2,1\"\n" << "first coordinate is row and second is column\n";

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

		if (movedPiece->getColor() != playerTurn)
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

std::pair<std::pair<int, int>, std::pair<int, int>> Game::parseCoords(std::string coords)
{
	bool filledFirst = false;
	std::pair<int, int> startCoords;
	std::pair<int, int> endCoords;
	for (int i = 0; i < coords.size(); i++)
	{
		char delim = coords[i];
		if (delim == '.')
		{
			filledFirst = true;
		}
		if (delim == ',')
		{
			if (!filledFirst)
			{
				int numRow = coords[i - 1] - 48;
				int numCol = coords[i + 1] - 48;
				startCoords.first = numRow;
				startCoords.second = numCol;

			}
			else
			{
				int numRow = coords[i - 1] - 48;
				int numCol = coords[i + 1] - 48;
				endCoords.first = numRow;
				endCoords.second = numCol;

			}
		}
	}
	return std::pair<std::pair<int, int>, std::pair<int, int>>(startCoords, endCoords);
}
