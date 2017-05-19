#include "Matrix.h"
#include "LoadedGame.h"
#include "WinConsole2.h"

void NewGame(Game& g1);

int main(int argc, char *argv[]) {
	if (argc == 1) {
		Matrix m{ 10, 20 };
		m.init();
		m.hideMines(10);
		NewGame(m);
	} else {
		LoadedGame g {};
		g.LoadFromFile(argv[1]);
		NewGame(g);
	}
	return 0;
}


#define KB_ENTER	13
#define KB_ESCAPE	27
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
	int status = 0;
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