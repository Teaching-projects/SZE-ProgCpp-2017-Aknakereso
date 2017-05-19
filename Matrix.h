#ifndef MATRIX_H
#define MATRIX_H

#include <time.h>
#include "Game.h"

class Matrix : public Game
{
public:
	Matrix(int rows, int cols);
	void hideMines(int count);

};

#endif // !MATRIX_H