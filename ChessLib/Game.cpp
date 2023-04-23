#include "Game.h"

void Game::run()
{
	enum turn
	{
		white = 0,
		black = 1
	};

	turn playerTurn = white;
	Board board(8, 8);
	board.setPiece({ 1, 0 }, std::make_unique<Pawn>(Piece::Color::Black));
	board.setPiece({ 1, 1 }, std::make_unique<Pawn>(Piece::Color::Black));
	board.setPiece({ 1, 2 }, std::make_unique<Pawn>(Piece::Color::Black));
	board.setPiece({ 1, 3 }, std::make_unique<Pawn>(Piece::Color::Black));
	board.setPiece({ 1, 4 }, std::make_unique<Pawn>(Piece::Color::Black));
	board.setPiece({ 1, 5 }, std::make_unique<Pawn>(Piece::Color::Black));
	board.setPiece({ 1, 6 }, std::make_unique<Pawn>(Piece::Color::Black));
	board.setPiece({ 1, 7 }, std::make_unique<Pawn>(Piece::Color::Black));

	board.setPiece({ 6, 0 }, std::make_unique<Pawn>(Piece::Color::White));
	board.setPiece({ 6, 1 }, std::make_unique<Pawn>(Piece::Color::White));
	board.setPiece({ 6, 2 }, std::make_unique<Pawn>(Piece::Color::White));
	board.setPiece({ 6, 3 }, std::make_unique<Pawn>(Piece::Color::White));
	board.setPiece({ 6, 4 }, std::make_unique<Pawn>(Piece::Color::White));
	board.setPiece({ 6, 5 }, std::make_unique<Pawn>(Piece::Color::White));
	board.setPiece({ 6, 6 }, std::make_unique<Pawn>(Piece::Color::White));
	board.setPiece({ 6, 7 }, std::make_unique<Pawn>(Piece::Color::White));

	board.setPiece({ 2, 1 }, std::make_unique<Pawn>(Piece::Color::White));

	do
	{
		clearTerminal();
		std::cout << "===============================================\n";
		std::cout << (playerTurn == turn::white ? "Whites turn" : "Blacks turn") << '\n' << '\n';
		std::cout << "q - quit\n";
		std::cout << "type comma seperated cordinates where start and\ndestination is dot seperated. ex." << " \"1,1.2,1\"\n" << "first coordinate is row and second is column\n";

		std::cout << "===============================================\n";
		board.printBoard();

		std::cout << "Your input: ";
		std::string input;
		std::cin >> input;
		std::cout << input << '\n';
		auto coords = parseCoords(input);

		Piece* movedPiece = board.getPiece(coords.first);
		auto moves = movedPiece->getValidMoves(&board, coords.first);
		//auto moves = board.getPawnMoves(coords.first);
		board.move(coords.first, coords.second);
	

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
