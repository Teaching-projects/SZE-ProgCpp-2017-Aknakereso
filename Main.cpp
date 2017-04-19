#include <iostream>
#include <conio.h>
#include "Matrix.h"
#include <Windows.h>

#define KB_ENTER	13 // 0x0D
#define KB_ESCAPE	27 // 0x1B
#define KB_UP		72 // 0x48
#define KB_LEFT		75 // 0x4B
#define KB_RIGHT	77 // 0x4D
#define KB_DOWN		80 // 0x50

void NewGame(int rows, int cols);


int main(int argc, char *argv[]) {
	NewGame(10, 20);
	return 0;
}


void NewGame(int rows, int cols) {
	Matrix m1{ rows, cols };
	int x = 0, y = 0;
	char c;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD homeCoords = { 0, 0 };

	m1.init();
	m1.hideMines(10);

	do {
		SetConsoleCursorPosition(hStdOut, homeCoords);
		m1.printM(x, y);
		c = _getch();
		switch (c) {
		case KB_LEFT	: if (x > 0) --x; break;
		case KB_RIGHT	: if (x < cols - 1) ++x; break;
		case KB_UP		: if (y > 0) --y; break;
		case KB_DOWN	: if (y < rows - 1) ++y; break;
		case KB_ENTER	: m1.selectField(x, y); break;
		}
	} while (c != KB_ESCAPE);
}