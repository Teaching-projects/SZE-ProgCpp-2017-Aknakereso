#include "Game.h"

Game::Game() : Signs(0), Clear(0) {}

void Game::printM(int posX, int posY) const {
	int i, j;
	short color;

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
			if (j == posX && i == posY) {
				SetColor(-color & 0x00FF);
			}

			switch (Values[i][j]) {
			case 0: std::cout << ' '; break;
			case 1: std::cout << '1'; break;
			case 2: std::cout << '2'; break;
			case 3: std::cout << '3'; break;
			case 4: std::cout << '4'; break;
			case 5: std::cout << '5'; break;
			case 6: std::cout << '6'; break;
			case 7: std::cout << '7'; break;
			case 8: std::cout << '8'; break;
			case 9: std::cout << '*'; break;
			case 10: std::cout << '#'; break;
			case 11: std::cout << 'O'; break;
			case 12: std::cout << '!'; break;
			case 13: std::cout << '?'; break;
			}

			if (j == posX && i == posY) {
				SetColor(color);
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

char Game::MinesAround(char X, char Y) const {
	const char dX[8] = { -1,  0, +1, -1, +1, -1,  0, +1 };
	const char dY[8] = { -1, -1, -1,  0,  0, +1, +1, +1 };
	char mines = 0;
	int i;

	for (i = 0; i < 8; ++i) {
		if ((X + dX[i] >= 0) && (X + dX[i] < Cols) &&
			(Y + dY[i] >= 0) && (Y + dY[i] < Rows) &&
			(Values[Y + dY[i]][X + dX[i]] == HIDDEN_MINE)) {
			++mines;
		}
	}
	return mines;
}

int Game::selectField(int x, int y) {
	const char dX[8] = { -1,  0, +1, -1, +1, -1,  0, +1 };
	const char dY[8] = { -1, -1, -1,  0,  0, +1, +1, +1 };

	char i;

	if (Values[y][x] >= 10/*== HIDDEN_FIELD*/) {	// Ha üres helyet választottunk, akkor
		if (Values[y][x] == HIDDEN_MINE) {		// ha a válsztott mezõn akna van, akkor
			Values[y][x] = MINE;				// mutassuk meg az aknát, és
			printM(x, y);
			return -1;						 	// vége a játéknak.
		}
		else {
			if (MinesAround(x, y) > 0) {			// Egyébként ha van körülötte akna, akkor
				Values[y][x] = MinesAround(x, y);	// mutassa, hogy mennyi.
			}
			else {								// Amúgy nézze meg a körülötte lévõket.
				Values[y][x] = FIELD_0;
				for (i = 0; i < 8; i++) {
					if ((x + dX[i] >= 0) && (x + dX[i] < Cols) &&
						(y + dY[i] >= 0) && (y + dY[i] < Rows)) {
						selectField(x + dX[i], y + dY[i]);
					}
				}
			}
			++Clear;
			if (Clear + Mines == Rows * Cols) {	// Megtaláltuk-e az összes aknát?
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