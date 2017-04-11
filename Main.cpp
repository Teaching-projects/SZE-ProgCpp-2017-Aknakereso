#include <iostream>
#include <conio.h>
#include "Matrix.h"
#include <Windows.h>

#define ROWS 10
#define COLS 20
#define KB_ENTER	13 // 0x0D
#define KB_ESCAPE	27 // 0x1B
#define KB_UP		72 // 0x48
#define KB_LEFT		75 // 0x4B
#define KB_RIGHT	77 // 0x4D
#define KB_DOWN		80 // 0x50


void main(void) {
	Matrix m1{ ROWS, COLS };
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
		case KB_LEFT: if (x > 0) --x; break;
		case KB_RIGHT: if (x < COLS - 1) ++x; break;
		case KB_UP: if (y > 0) --y; break;
		case KB_DOWN: if (y < ROWS - 1) ++y; break;
		case KB_ENTER: break;
		}
	} while (c != KB_ESCAPE);
}
