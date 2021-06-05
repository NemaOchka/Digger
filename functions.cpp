#include <Windows.h>

using namespace std;

void ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

int Check_Pressed_Button() {
	if (GetKeyState(VK_UP) == -127 || GetKeyState(VK_UP) == -128) {
		return 1;
	}
	else if (GetKeyState(VK_RIGHT) == -127 || GetKeyState(VK_RIGHT) == -128) {
		return 2;
	}
	else if (GetKeyState(VK_DOWN) == -127 || GetKeyState(VK_DOWN) == -128) {
		return 3;
	}
	else if (GetKeyState(VK_LEFT) == -127 || GetKeyState(VK_LEFT) == -128) {
		return 4;
	}
	else return 0;
}