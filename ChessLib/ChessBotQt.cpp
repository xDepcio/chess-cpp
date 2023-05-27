#include <sstream>
#include <QtCoreApplication>
#include "ChessBotQt.h"

const std::string

ChessBot::stockfishName = "stockfish";

QString ChessBot::getStockfishOutput(const char* command)
{
	QProcess stockfish;

	// Initialize stockfish
	stockfish.start(ChessBot::stockfishName.c_str());

	// Wait for start
	if (!stockfish.waitForStarted()) {
		qDebug() << "Failed to start Stockfish Engine";
		return "";
	}

	// write commands to Stockfish's stdin
	stockfish.write("uci\n"); // Initialize UCI node
	stockfish.write("ucinewgame\n"); // Start a new gane
	stockfish.write(command); // Set the chessboard position in FEN notation
	stockfish.write("go depth 10\n"); // Ask Stockfish to calculate the best move with depth 10

	while (true)
	{
		stockfish.waitForReadyRead();
		QString output = stockfish.readAll();
		if (output.contains("bestmove"))
		{
			stockfish.kill();
			return output;
		}
	}

	stockfish.kill();
	return "";
}

QString ChessBot::getStockfishOutput(std::string fen)
{
	std::stringstream fen_pos;
	fen_pos << "position fen " << fen << "\n";
	return ChessBot::getStockfishOutput(fen_pos.str().c_str());
}

std::string ChessBot::extractMove(QString stockfishOutput)
{
	std::string fish_out = stockfishOutput.toStdString();
	std::string pat = "bestmove ";
	auto index = fish_out.find(pat);
	return fish_out.substr(index + pat.size(), 4);
}

std::string ChessBot::getBestMove(std::string fenPosition) const
{
	auto moveStr = extractMove(getStockfishOutput(fenPosition));
	auto from = moveStr.substr(0, 2);
	auto to = moveStr.substr(2, 4);

	std::stringstream move_input;
	move_input << from << "-" << to;
	return move_input.str();
}


