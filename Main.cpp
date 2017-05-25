#include "Matrix.h"
#include "LoadedGame.h"
#include "WinConsole2.h"

#define MIN_WIDTH	5
#define MIN_HEIGHT	5
#define MIN_MINES	5
#define MAX_WIDTH	30
#define MAX_HEIGHT	30

void NewGame(Game& g1);

int main(int argc, char *argv[]) {
	// Default game
	if (argc == 1) {
		Matrix m{ 10, 20, 10 };
		NewGame(m);
	// Game loaded from file
	} else if (argc == 2) {
		LoadedGame g { argv[1] };
		if (g.FileOK == 0) return 1; 
		NewGame(g);
	// Custom game
	} else if (argc == 4) {
		int Rows = min(max(MIN_HEIGHT, atoi(argv[1])), MAX_HEIGHT);
		int Cols = min(max(MIN_WIDTH, atoi(argv[2])), MAX_WIDTH);
		int Mines = min(max(MIN_MINES, atoi(argv[3])), Rows * Cols * 0.2);
		// Messages on wrong parameter
		if (atoi(argv[1]) < MIN_HEIGHT || atoi(argv[1]) > MAX_HEIGHT) {
			std::cout << "Number of rows (argument 1) must be between "
				<< MIN_HEIGHT << " and " << MAX_HEIGHT << "! "
				<< "Using " << Rows << std::endl;
		}
		if (atoi(argv[2]) < MIN_WIDTH || atoi(argv[2]) > MAX_WIDTH) {
			std::cout << "Number of columns (argument 2) must be between "
				<< MIN_WIDTH << " and " << MAX_WIDTH << "! "
				<< "Using " << Cols << std::endl;
		}
		if (atoi(argv[3]) < MIN_MINES || atoi(argv[3]) > Rows * Cols * 0.2) {
			std::cout << "Number of mines (argument 3) must be between "
				<< MIN_MINES << " and " << (Rows * Cols * 0.2) << "! "
				<< "Using " << Mines << std::endl;
		}
		std::cout << "Press ENTER to start game!";
		std::cin.ignore();

		Matrix m{ Rows, Cols, Mines };
		NewGame(m);
	}
	return 0;
}


#define KB_ENTER	13
#define KB_ESCAPE	27
#define KB_SPACE	32
#define KB_UP		72
#define KB_LEFT		75
#define KB_RIGHT	77
#define KB_DOWN		80
#define KB_b		98
#define KB_c		99
#define KB_B		67
#define KB_C		68
#define STATUS_DEAD -1
#define STATUS_ALIVE 0
#define STATUS_DONE 1

void NewGame(Game& g1) {
	int x = 0;
	int y = 0;
	int status = STATUS_ALIVE;
	char c;
	short OriginalColor;
	GetColor(OriginalColor);

	ClearScreen();
	do {
		g1.printM(x, y);
		c = _getch();
		switch (c) {
			case KB_LEFT: if (x > 0) --x; break;
			case KB_RIGHT: if (x < g1.GetCols() - 1) ++x; break;
			case KB_UP: if (y > 0) --y; break;
			case KB_DOWN: if (y < g1.GetRows() - 1) ++y; break;
			case KB_ENTER: status = g1.selectField(x, y); break;
			case KB_b: SelectBackgroudColor(); break;
			case KB_c: SelectForegroudColor(); break;
			case KB_B: SelectBackgroudColor(); break;
			case KB_C: SelectForegroudColor(); break;
			case KB_SPACE: g1.markField(x, y); break;
		}
	} while (c != KB_ESCAPE && status == STATUS_ALIVE);

	if (status == STATUS_DEAD) {
		std::cout << static_cast<char>(7) << "GAME OVER!" << std::endl;
		_getch();
	} else {
		if (status == STATUS_DONE) {
			std::cout << "WELL DONE!" << std::endl;
			_getch();
		}
	}
	SetColor(OriginalColor); // Restore console color
	ClearScreen();
}