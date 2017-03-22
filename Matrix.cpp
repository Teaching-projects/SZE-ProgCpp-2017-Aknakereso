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