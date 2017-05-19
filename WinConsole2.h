#ifndef WINCONSOLE2_H
#define WINCONSOLE2_H

#include <conio.h>
#include <iostream>
#include "WinConsole.h"

#define KB_ENTER	13
#define KB_ESCAPE	27
#define KB_UP		72
#define KB_LEFT		75
#define KB_RIGHT	77
#define KB_DOWN		80
#define KB_b		98
#define KB_c		99


void PrintPalette(char x, char y) {
	short OriginalColor;
	GetColor(OriginalColor);
	short _x, _y;

	for (_y = 0; _y < 2; ++_y) {
		for (_x = 0; _x < 8; _x++) {
			SetColor(_x * 0x10 + _y * 0x0080);
			if ((_x == x) && (_y == y)) {
				SetColor((_x * 0x10 + _y * 0x0080) + (1 - _y) * 0x000F);
				std::cout << '*';
			} else {
				std::cout << ' ';
			}
			SetColor(OriginalColor);
		}
		std::cout << std::endl;
	}
}

void ClearScreen(void) {
	HANDLE hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	// Get the number of cells in the current buffer
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	// Fill the entire buffer with spaces
	if (!FillConsoleOutputCharacter(
		hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count
	)) return;

	// Fill the entire buffer with the current colors and attributes
	if (!FillConsoleOutputAttribute(
		hStdOut, csbi.wAttributes, cellCount, homeCoords, &count
	)) return;

	// Move the cursor home
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

short SelectForegroudColor(void) {
	char x = 0, y = 0, c = 0;
	short CurrentColor;

	do {
		switch (c) {
		case KB_LEFT:	if (x > 0) --x; break;
		case KB_RIGHT:	if (x < 7) ++x; break;
		case KB_UP:		if (y > 0) --y; break;
		case KB_DOWN:	if (y < 1) ++y; break;
		}
		ClearScreen();
		PrintPalette(x, y);
		c = _getch();
	} while ((c != KB_ESCAPE) && (c != KB_ENTER));

	if (c = KB_ENTER) {
		GetColor(CurrentColor);
		CurrentColor = CurrentColor & 0x00F0; // Background: unchanged, foreground: 0
		CurrentColor = CurrentColor + x * 0x0001 + y * 0x0008;
		SetColor(CurrentColor);
	}

	return CurrentColor;
}

short SelectBackgroudColor(void) {
	char x = 0, y = 0, c = 0;
	short CurrentColor;

	do {
		switch (c) {
		case KB_LEFT:	if (x > 0) --x; break;
		case KB_RIGHT:	if (x < 7) ++x; break;
		case KB_UP:		if (y > 0) --y; break;
		case KB_DOWN:	if (y < 1) ++y; break;
		}
		ClearScreen();
		PrintPalette(x, y);
		c = _getch();
	} while ((c != KB_ESCAPE) && (c != KB_ENTER));

	if (c = KB_ENTER) {
		// Set background color only
		GetColor(CurrentColor);
		CurrentColor = CurrentColor & 0x000F;
		CurrentColor = CurrentColor + x * 0x0010 + y * 0x0080;
		SetColor(CurrentColor);
	}

	return CurrentColor;
}

#endif // WINCONSOLE2_H