#include <Windows.h>

void CenWin()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 225, 550, TRUE);

	HWND   hwndScreen;
	RECT   rectScreen;
	int    ConsolePosX;
	int    ConsolePosY;
	hwndScreen = GetDesktopWindow();
	GetWindowRect(hwndScreen, &rectScreen);
	ConsolePosX = (rectScreen.right - 225) >> 1;
	ConsolePosY = (rectScreen.bottom - 550) >> 1;
	SetWindowPos(GetConsoleWindow(), HWND_NOTOPMOST, ConsolePosX, ConsolePosY, 265, 530, SWP_NOOWNERZORDER);
}
