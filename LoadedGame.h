#ifndef LOADEDGAME_H
#define LOADEDGAME_H

#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"

class LoadedGame
{
public:
	LoadedGame();
	int LoadFromFile(char *FileName);
private:
	int *m;
	int rows;
	int cols;
	int mines;

};

LoadedGame::LoadedGame() : m(nullptr), rows(0) , cols(0), mines(0) {}

int LoadedGame::LoadFromFile(char *FileName) {
	std::ifstream F;
	std::string s;

	F.open(FileName);
	if (F.is_open()) {
		std::getline(F, s);
		cols = s.length();
		F.seekg(0);
		while (std::getline(F, s)) {
			for (int i = 0; i < cols; i++) {
				if (s[i] == 'O') {
					++mines;
				}
			}
			++rows;
		}
		F.close();
		std::cout << cols << " " << rows << ' ' << mines << std::endl;
		return 0;
	} else {
		std::cout << "Unable to open file";
		return 1;
	}
}



#endif // LOADEDGAME_H