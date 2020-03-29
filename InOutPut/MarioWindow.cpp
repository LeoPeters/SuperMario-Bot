#include <windows.h>
#include <iostream>
#include "MarioWindow.h"

HWND MarioWindow::getMarioWindow(LPCTSTR path) {
	HWND window = MarioWindow::findMarioWindow();
	int i = 0;
	while (i <= 1) {
		if (window == NULL) {
			ShellExecute(NULL, L"OPEN", path, NULL, NULL, SW_SHOWNORMAL);
			Sleep(1500);
			window = MarioWindow::findMarioWindow();
		}
		else {
			printf("window found: %X \n", (unsigned int)window);
			return window;
		}
		i++;
	}
	printf("Can't Execute Mesen\n");
	return window;

	;
}

HWND MarioWindow::findMarioWindow() {
	HWND mainWindow = ::FindWindow(L"WindowsForms10.Window.8.app.0.1e84ccb_r6_ad1", NULL);
	HWND window = FindWindowEx(mainWindow, NULL, NULL, NULL);
	HWND window2 = FindWindowEx(mainWindow, window, NULL, NULL);
	window = FindWindowEx(window2, NULL, NULL, NULL);
	window = FindWindowEx(window2, window, NULL, NULL);
	return window;
}