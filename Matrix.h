#ifndef MATRIX_H
#define MATRIX_H

#include <time.h>
#include "Game.h"

class Matrix : public Game
{
public:
	Matrix(int rows, int cols, int mines);

private:
	void hideMines();

};

#endif // !MATRIX_H