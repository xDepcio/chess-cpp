#pragma once

#include <string>
#include <QString>

class ChessBot
{
	/*
	Requires stockfish to be installed in PATH
	*/
private:

	int difficultyLevel = 10;

	static const std::string stockfishName;

	static QString getStockfishOutput(const char* command);

	static QString getStockfishOutput(std::string fen);

	static std::string extractMove(QString stockfishOutput);


public:
	std::string getBestMove(std::string fenPosition) const;

	void setDifficulty(int level);

};