// Implemantation of class Matrix

#include "Matrix.h"
#include <iostream>

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

void Matrix::hideMines(int count) {
	if (count < Matrix::values.size() * Matrix::values[0].size()) {
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