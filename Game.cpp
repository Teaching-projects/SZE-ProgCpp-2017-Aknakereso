#include "Game.h"

Game::Game() : Signs(0), Clear(0) {}

void Game::printM(int x, int y) const {
	int i, j;
	short color;
	const char c[16] = { 
		' ', '1', '2', '3', '4', '5', '6', '7', 
		'8', '*', '#', '#', '!', '!', '?', '?' };

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD homeCoords = { 0, 0 };
	SetConsoleCursorPosition(hStdOut, homeCoords);
	GetColor(color);

	// Upper frame
	putchar(-55);
	for (i = 0; i < Cols; i++) {
		putchar(-51);
	}
	putchar(-69);
	std::cout << std::endl;

	// Vector elements
	for (i = 0; i < Rows; i++) {
		putchar(-70);
		for (j = 0; j < Cols; j++) { 
			if (j == x && i == y) {
				SetColor(-color & 0x00FF);
				std::cout << c[Values[i][j]];
				SetColor(color);
			} else {
				std::cout << c[Values[i][j]];
			}
		}
		putchar(-70);
		std::cout << std::endl;
	}

	// Bottom frame
	putchar(-56);
	for (i = 0; i < Cols; i++) {
		putchar(-51);
	}
	putchar(-68);
	std::cout << std::endl;
}

char Game::MinesAround(char x, char y) const {
	const char dX[8] = { -1,  0, +1, -1, +1, -1,  0, +1 };
	const char dY[8] = { -1, -1, -1,  0,  0, +1, +1, +1 };
	char mines = 0;
	int i;

	for (i = 0; i < 8; ++i) {
		/*if ((x + dX[i] >= 0) && (x + dX[i] < Cols) &&
			(y + dY[i] >= 0) && (y + dY[i] < Rows) &&
			(isMine(Values[y + dY[i]][x + dX[i]]))) {
			++mines;
		}*/
		mines += (
			(x + dX[i] >= 0) && (x + dX[i] < Cols) &&
			(y + dY[i] >= 0) && (y + dY[i] < Rows) &&
			(isMine(Values[y + dY[i]][x + dX[i]])));
	}
	return mines;
}

int Game::selectField(int x, int y) {
	const char dX[8] = { -1,  0, +1, -1, +1, -1,  0, +1 };
	const char dY[8] = { -1, -1, -1,  0,  0, +1, +1, +1 };

	char i;

	if (Values[y][x] >= 10 /*== HIDDEN_FIELD*/ &&
		Values[y][x] < 12 /*!= MARKED_FIELD*/) {	// Ha üres helyet választottunk, akkor
		if (Values[y][x] == HIDDEN_MINE) {			// ha a válsztott mezõn akna van, akkor
			Values[y][x] = MINE;					// mutassuk meg az aknát, és
			printM(x, y);
			return -1;								// vége a játéknak.
		} else {
			if (MinesAround(x, y) > 0) {			// Egyébként ha van körülötte akna, akkor
				Values[y][x] = MinesAround(x, y);	// mutassa, hogy mennyi.
			} else {								// Amúgy nézze meg a körülötte lévõket.
				Values[y][x] = FIELD_0;
				for (i = 0; i < 8; i++) {
					if ((x + dX[i] >= 0) && (x + dX[i] < Cols) &&
						(y + dY[i] >= 0) && (y + dY[i] < Rows)) {
						selectField(x + dX[i], y + dY[i]);
					}
				}
			}
			++Clear;
			if (Clear + Mines == Rows * Cols) {		// Megtaláltuk-e az összes aknát?
				printM(x, y);
				return 1;
			}
		}
	}
	return 0;
}

int Game::GetCols() const {
	return Cols;
}

int Game::GetRows() const {
	return Rows;
}

void Game::markField(int x, int y) {
	if (Values[y][x] >= 10/*== HIDDEN_FIELD*/) {
		if (Values[y][x] < 14) {
			Values[y][x] += 2;
		} else {
			Values[y][x] -= 4;
		}
		printM(x, y);
	}
}

bool Game::isMine(char f) const {
	return (f & 0x09) == 0x09;
}