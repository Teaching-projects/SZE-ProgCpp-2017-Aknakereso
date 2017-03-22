#include <iostream>
#include <conio.h>	// _getch
#include "Matrix.h"


void main(void) {
	Matrix m1{10, 10};

	m1.init();
	m1.hideMines(10);
	m1.print();

	getchar();
}