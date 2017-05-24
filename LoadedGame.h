#ifndef LOADEDGAME_H
#define LOADEDGAME_H

#include <fstream>
#include <string>
#include "Game.h"

class LoadedGame : public Game
{
public:
	int FileOK;
	LoadedGame(char *filename);

private:
	char *FileName;
	int LoadFromFile();

};

#endif // LOADEDGAME_H