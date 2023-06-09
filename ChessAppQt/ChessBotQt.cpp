#include <sstream>
#include <filesystem>
#include <QtCore>
#include "ChessBotQt.h"

using std::filesystem::current_path;



const std::string ChessBot::stockfishName = ".\\stockfish";

int ChessBot::difficultyLevel = 20;

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
	stockfish.write("setoption name UCI_LimitStrength value true\n");
	std::stringstream skillPrompt;
	//skillPrompt << "setoption name Skill Level value " << difficultyLevel << "\n";
	//stockfish.write(skillPrompt.str().c_str());
	stockfish.write("setoption name Skill Level value 1\n");


	stockfish.write(command); // Set the chessboard position in FEN notation

	
	std::stringstream depPrompt;
	depPrompt << "go depth " << (difficultyLevel / 2) + 1 << "\n";
	stockfish.write(depPrompt.str().c_str());
	//stockfish.write("go depth 10\n");

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


void ChessBot::setDifficulty(int difflevel)
{
	if (difflevel < 1) 
	{
		difficultyLevel = 1;
	}
	else if (difflevel > 20)
	{
		difficultyLevel = 20;
	}
	else
	{
		difficultyLevel = difflevel;
	}
}