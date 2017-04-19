// Implemantation of class Matrix

#include <iostream>
#include "Matrix.h"
#include "WinConsole.h"

Matrix::Matrix(int rows, int cols)
{
	Matrix::values.resize(rows);
	for (int y = 0; y < rows; ++y) {
		Matrix::values[y].resize(cols);
		for (int x = 0; x < rows; ++x) {
			Matrix::values[y][x] = HIDDEN_FIELD;
		}
	}
}

void Matrix::init() {
	int x, y;

	for (y = 0; y < Matrix::values.size(); ++y) {
		for (x = 0; x < Matrix::values[y].size(); ++x) {
			Matrix::values[y][x] = HIDDEN_FIELD;
		}
	}
}

void Matrix::print() const {
	char x , y;

	for (y = 0; y < Matrix::values.size(); ++y) {
		for (x = 0; x < Matrix::values[y].size(); ++x) {
			std::cout << static_cast<int>(Matrix::values[y][x]) << " ";
		}
		std::cout << std::endl;
	}
}

// Print matrix with frame and selection
void Matrix::printM(int posX, int posY) const {
	int i, j;
	int rows = values.size();
	int cols = values[0].size();
	short color;

	GetColor(color);

	// Upper frame
	putchar(-55);
	for (i = 0; i < cols; i++) {
		putchar(-51);
	}
	putchar(-69);
	std::cout << std::endl;

	// Vector elements
	for (i = 0; i < rows; i++) {
		cols = values[i].size();
		putchar(-70);
		for (j = 0; j < cols; j++) {
			if (j == posX && i == posY) {
				SetColor(-color & 0x00FF);
			}

			switch (values[i][j]) {
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
	for (i = 0; i < cols; i++) {
		putchar(-51);
	}
	putchar(-68);
	std::cout << std::endl;
}

void Matrix::hideMines(int count) {
	if (count < Matrix::values.size() * Matrix::values[0].size()) {
		Matrix::Mines = count;
		int i = 0;

		while (i < count) {
			int x, y;
			x = rand() % Matrix::values[0].size();
			y = rand() % Matrix::values.size();
			if (Matrix::values[y][x] == HIDDEN_FIELD) {
				Matrix::values[y][x] = HIDDEN_MINE;
				++i;
			}
		}
	}
}

// Returns how many mines there are around a field
char Matrix::MinesAround(char X, char Y) const {
	const signed char dX[8] = { -1,  0, +1, -1, +1, -1,  0, +1 };
	const signed char dY[8] = { -1, -1, -1,  0,  0, +1, +1, +1 };
	char mines = 0;
	char i;

	for (i = 0; i < 8; ++i) {
		if ((X + dX[i] >= 0) && (X + dX[i] < Matrix::values[i].size()) &&
			(Y + dY[i] >= 0) && (Y + dY[i] < Matrix::values.size()) &&
			(Matrix::values[Y + dY[i]][X + dX[i]] == HIDDEN_MINE)) {
			++mines;
		}
	}
	return mines;
}

void Matrix::selectField(int x, int y) {
	const char dX[8] = { -1,  0, +1, -1, +1, -1,  0, +1 };
	const char dY[8] = { -1, -1, -1,  0,  0, +1, +1, +1 };

	unsigned char i;
	unsigned short dlg;

	int Clear = 0;
	int mines = Matrix::Mines;
	int Rows = Matrix::values.size();
	int Cols = Matrix::values[0].size();


	if (values[y][x] == HIDDEN_FIELD)			// Ha üres helyet választottunk, akkor
		if (values[y][x] == HIDDEN_MINE) {		// ha a válsztott mezõn akna van, akkor
			values[y][x] = MINE;				// mutassuk meg az aknát, és
			printM(x, y);
			putchar(7);
			std::cout << "Game over!\n";      	// vége a játéknak.
			//NewGame();                       	// új játék kezdése.
		}
		else {
			if (MinesAround(x, y) > 0) {			// Egyébként ha van körülötte akna, akkor
				values[y][x] = MinesAround(x, y);	// mutassa, hogy mennyi.
				++Clear;
			}
			else {				// Amúgy nézze meg a körülötte lévõket.
				values[y][x] = FIELD_0;
				++Clear;
				for (i = 0; i < 8; i++) {
					if ((x + dX[i] >= 0) && (x + dX[i] < Cols) &&
						(y + dY[i] >= 0) && (y + dY[i] < Rows)) {
						selectField(x + dX[i], y + dY[i]);
					}
				}
			}
			if (Clear + mines == Rows * Cols) {	// Megtaláltuk-e az össze aknát?
				printM(x, y);
/*				std::cout << "Kezdesz új játékot?" << std::endl;
				if (getchar() = 'y') {
					NewGame;
				}*/
			}
		}

}