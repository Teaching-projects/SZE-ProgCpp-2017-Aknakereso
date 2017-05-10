#ifndef LOADEDGAME_H
#define LOADEDGAME_H

#include <fstream>
#include <string>
#include "Game.h"

class LoadedGame : public Game
{
public:
	LoadedGame();
	int LoadFromFile(char *FileName);

};

#endif // LOADEDGAME_H