#ifndef WINCONSOLE_H
#define WINCONSOLE_H

#include <Windows.h>

static bool GetColor(short &color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
		return false;
	color = info.wAttributes;
	return true;
}

static bool SetColor(short color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(hConsole, color);
}

#endif