#include <iostream>
#include "Matrix.h"


void main(void) {
	Matrix m1{10, 10};

	m1.init();
	m1.hideMines(10);
	std::cout << "P�lya akn�kkal egy�tt:" << std::endl;
	m1.print();
	std::cout << std::endl;
	std::cout << "Akn�k sz�ma az adott mez�k k�r�l:" << std::endl;
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			std::cout << (int)m1.MinesAround(x, y) << " ";
		}
		std::cout << std::endl;
	}

	getchar();
}