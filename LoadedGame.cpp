#include "LoadedGame.h"

LoadedGame::LoadedGame(char *filename) : FileName(filename) {
	FileOK = LoadFromFile();
}

int LoadedGame::LoadFromFile() {
	std::ifstream F;
	std::string s;
	int filesize;

	F.open(FileName);
	if (F.is_open()) {
		// Count rows and columns
		std::getline(F, s);
		Cols = s.length();
		F.seekg(0, F.end);
		filesize = static_cast<int>(F.tellg()) - Cols * 2;// Filesize without end of line
		Rows = filesize / Cols;
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
		// Too many mines
		if (Mines > 0.2 * Rows * Cols) {
			std::cout << "This is a real hard game!" << std::endl;
			std::cout << Cols << " columns, " << Rows << " rows, " << Mines << " mines!" << std::endl;
			std::cout << "Press ENTER to continue!" << std::endl;
			std::cin.ignore();
		}
		return 1;
	}
	else {
		std::cout << "Unable to open file: " << FileName;
		return 0;
	}
}