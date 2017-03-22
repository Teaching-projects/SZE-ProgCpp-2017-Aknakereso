// Interface of class Matrix

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

/**
	M�trix oszt�ly egy p�lya �llapot�nak t�rol�s�hoz
**/
class Matrix
{
public:
	Matrix(int rows, int cols);
	void init();
	void print() const;
	void hideMines(int count);

private:
	std::vector< std::vector<char> > values;
	const char FIELD_0			= 0;	// Revealed field, no mines around
	const char FIELD_1			= 1;	// Revealed field, 1 mine around
	const char FIELD_2			= 2;	// Revealed field, 2 mines around
	const char FIELD_3			= 3;	// Revealed field, 3 mines around
	const char FIELD_4			= 4;	// Revealed field, 4 mines around
	const char FIELD_5			= 5;	// Revealed field, 5 mines around
	const char FIELD_6			= 6;	// Revealed field, 6 mines around
	const char FIELD_7			= 7;	// Revealed field, 7 mines around
	const char FIELD_8			= 8;	// Revealed field, 8 mines around
	const char MINE				= 9;	// Revealed mine
	const char HIDDEN_FIELD		= 10;	// Unrevealed field
	const char HIDDEN_MINE		= 11;	// Unrevealed mine
	const char MARK_FLAG		= 12;	// Unrevealed field marked as mine
	const char MARK_SAFE		= 13;	// Unrevealed field marked as safe

};

#endif // !MATRIX_H
