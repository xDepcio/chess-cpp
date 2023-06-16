#pragma once
#include <sstream>
#include <string>
#include <QString>

class ChessBot
{

private:

	static int difficultyLevel;

	static const std::string stockfishName;

	static QString getStockfishOutput(const char* command);

	static QString getStockfishOutput(std::string fen);

	static std::string extractMove(QString stockfishOutput);


public:
	std::string getBestMove(std::string fenPosition) const;

	void setDifficulty(int level);

};