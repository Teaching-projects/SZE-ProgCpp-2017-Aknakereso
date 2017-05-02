#include <iostream>
#include <conio.h>
#include "Matrix.h"
//#include "LoadedGame.h"

#define KB_ENTER	13
#define KB_ESCAPE	27
#define KB_UP		72
#define KB_LEFT		75
#define KB_RIGHT	77
#define KB_DOWN		80

void NewGame(int rows, int cols, int mines);


/*int main(int argc, char *argv[]) {
	LoadedGame g1 {};
	g1.LoadFromFile("D:\\Programozás C++-ban\\Project4\\Game1.txt");
	std::cin.ignore();
	return 0;
}*/

int main(int argc, char *argv[]) {
	NewGame(10, 20, 10);
	return 0;
}


void NewGame(int rows, int cols, int mines) {
	Matrix m1{ rows, cols };
	int x = 0, y = 0;
	char c;

	m1.init();
	m1.hideMines(mines);

	int alive = 1;
	do {
		m1.printM(x, y);
		c = _getch();
		switch (c) {
			case KB_LEFT	: if (x > 0) --x; break;
			case KB_RIGHT	: if (x < cols - 1) ++x; break;
			case KB_UP		: if (y > 0) --y; break;
			case KB_DOWN	: if (y < rows - 1) ++y; break;
			case KB_ENTER	: alive = m1.selectField(x, y); break;
		}
	} while (c != KB_ESCAPE && alive);

	if (!alive) {
		std::cout << (char)7 << "GAME OVER!" << std::endl;
		_getch();
	}
}