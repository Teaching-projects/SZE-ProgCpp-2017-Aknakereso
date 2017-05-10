#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "WinConsole.h"

class Game
{
public:
	Game();
	void printM(int posX, int posY) const;
	int selectField(int x, int y);
	int GetCols() const;
	int GetRows() const;

protected:
	std::vector< std::vector<char> > Values;
	int Rows;
	int Cols;
	int Mines;
	int Signs;
	int Clear;
	const char FIELD_0 = 0;	// Revealed field, no mines around
	const char FIELD_1 = 1;	// Revealed field, 1 mine around
	const char FIELD_2 = 2;	// Revealed field, 2 mines around
	const char FIELD_3 = 3;	// Revealed field, 3 mines around
	const char FIELD_4 = 4;	// Revealed field, 4 mines around
	const char FIELD_5 = 5;	// Revealed field, 5 mines around
	const char FIELD_6 = 6;	// Revealed field, 6 mines around
	const char FIELD_7 = 7;	// Revealed field, 7 mines around
	const char FIELD_8 = 8;	// Revealed field, 8 mines around
	const char MINE = 9;	// Revealed mine
	const char HIDDEN_FIELD = 10;	// Unrevealed field
	const char HIDDEN_MINE = 11;	// Unrevealed mine
	const char MARK_FLAG = 12;	// Unrevealed field marked as mine
	const char MARK_SAFE = 13;	// Unrevealed field marked as safe
	char MinesAround(char X, char Y) const;
};

#endif // GAME_H