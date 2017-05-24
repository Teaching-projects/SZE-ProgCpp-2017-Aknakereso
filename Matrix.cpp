#include "Matrix.h"

Matrix::Matrix(int rows, int cols, int mines)
{
	Rows = rows;
	Cols = cols;
	Mines = mines;
	Values.resize(rows);
	for (int y = 0; y < rows; ++y) {
		Values[y].resize(cols);
		for (int x = 0; x < cols; ++x) {
			Values[y][x] = HIDDEN_FIELD;
		}
	}
	hideMines();
}

void Matrix::hideMines() {
	srand(time(NULL));
	if (Mines < Rows * Cols) {
		int i = 0;

		while (i < Mines) {
			int x, y;
			x = rand() % Cols;
			y = rand() % Rows;
			if (Values[y][x] == HIDDEN_FIELD) {
				Values[y][x] = HIDDEN_MINE;
				++i;
			}
		}
	}
}