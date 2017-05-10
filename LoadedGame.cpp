#include "LoadedGame.h"

LoadedGame::LoadedGame() {}

int LoadedGame::LoadFromFile(char *FileName) {
	std::ifstream F;
	std::string s;

	F.open(FileName);
	if (F.is_open()) {
		// Count rows and columns
		std::getline(F, s);
		Cols = s.length();
		F.seekg(0, F.end);
		Rows = F.tellg() / Cols - 1;
		F.seekg(0, F.beg);
		// Resize vector
		int y;
		Values.resize(Rows);
		for (y = 0; y < Rows; ++y) {
			Values[y].resize(Cols);
		}
		// Read
		y = 0;
		while (std::getline(F, s)) {
			for (int x = 0; x < Cols; x++) {
				if (s[x] == 'O') {
					++Mines;
					Values[y][x] = HIDDEN_MINE;
				}
				else {
					Values[y][x] = HIDDEN_FIELD;
				}
			}
			++y;
		}
		F.close();
		std::cout << Cols << " " << Rows << ' ' << Mines << std::endl;
		return 0;
	}
	else {
		std::cout << "Unable to open file";
		return 1;
	}
}