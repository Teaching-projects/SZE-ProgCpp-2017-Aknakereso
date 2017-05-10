#include "Matrix.h"

Matrix::Matrix(int rows, int cols)
{
	Rows = rows;
	Cols = cols;
	Values.resize(rows);
	for (int y = 0; y < rows; ++y) {
		Values[y].resize(cols);
		for (int x = 0; x < rows; ++x) {
			Values[y][x] = HIDDEN_FIELD;
		}
	}
}

void Matrix::init() {
	int x, y;

	for (y = 0; y < Rows; ++y) {
		for (x = 0; x < Cols; ++x) {
			Values[y][x] = HIDDEN_FIELD;
		}
	}
}

void Matrix::hideMines(int count) {
	srand(time(NULL));
	if (count < Rows * Cols) {
		Mines = count;
		int i = 0;

		while (i < count) {
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