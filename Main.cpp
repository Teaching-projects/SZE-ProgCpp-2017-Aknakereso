#include <conio.h>
#include "Matrix.h"
#include "LoadedGame.h"

#define KB_ENTER	13
#define KB_ESCAPE	27
#define KB_UP		72
#define KB_LEFT		75
#define KB_RIGHT	77
#define KB_DOWN		80

void NewGame(Game& g1);
void NewGame(int rows, int cols, int mines);


int main(int argc, char *argv[]) {
	//LoadedGame g1 {};
	//g1.LoadFromFile("D:\\Programozás C++-ban\\Project4\\Game1.txt");
	//NewGame(g1);
	NewGame(10, 20, 10);

	return 0;
}


#define STATUS_DEAD -1
#define STATUS_ALIVE 0
#define STATUS_DONE 1

void NewGame(int rows, int cols, int mines) {
	Matrix m1{ rows, cols };
	int x = 0, y = 0;
	char c;

	m1.init();
	m1.hideMines(mines);

	int status = 0;
	do {
		m1.printM(x, y);
		c = _getch();
		switch (c) {
			case KB_LEFT	: if (x > 0) --x; break;
			case KB_RIGHT	: if (x < cols - 1) ++x; break;
			case KB_UP		: if (y > 0) --y; break;
			case KB_DOWN	: if (y < rows - 1) ++y; break;
			case KB_ENTER	: status = m1.selectField(x, y); break;
		}
	} while (c != KB_ESCAPE && status == STATUS_ALIVE);

	if (status == STATUS_DEAD) {
		std::cout << static_cast<char>(7) << "GAME OVER!" << std::endl;
		_getch();
	} else {
		if (status == STATUS_DONE) {
			std::cout << "WELL DONE!" << std::endl;
			_getch();
		}
	}
}

void NewGame(Game& g1) {
	int x = 0;
	int y = 0;
	int status = 0;
	char c;

	do {
		g1.printM(x, y);
		c = _getch();
		switch (c) {
		case KB_LEFT: if (x > 0) --x; break;
		case KB_RIGHT: if (x < g1.GetCols() - 1) ++x; break;
		case KB_UP: if (y > 0) --y; break;
		case KB_DOWN: if (y < g1.GetRows() - 1) ++y; break;
		case KB_ENTER: status = g1.selectField(x, y); break;
		}
	} while (c != KB_ESCAPE && status == STATUS_ALIVE);

	if (status == STATUS_DEAD) {
		std::cout << static_cast<char>(7) << "GAME OVER!" << std::endl;
		_getch();
	} else {
		if (status == STATUS_DONE) {
			std::cout << "WELL DONE!" << std::endl;
			_getch();
		}
	}
}