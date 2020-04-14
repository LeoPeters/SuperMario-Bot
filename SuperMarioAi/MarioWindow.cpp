
#include <iostream>
#include "MarioWindow.h"

HWND MarioWindow::getMarioWindow(LPCTSTR path) {
	MarioWindow::closeMarioApp();
	HWND mwindow=NULL;
	//Sleep(1000);
	ShellExecute(mwindow, L"OPEN", path, NULL, NULL, SW_SHOWNORMAL);
	Sleep(2000);
	
	HWND window = MarioWindow::findMarioWindow();
	std::cout << "Windowm Nr: " << mwindow << std::endl;
	std::cout <<"Window Nr: "<< window << std::endl;
	return window;

	;
}

HWND MarioWindow::findMarioWindow() {
	HWND mainWindow = ::FindWindow(NULL, L"Mesen");
	HWND window = FindWindowEx(mainWindow, NULL, NULL, NULL);
	HWND window2 = FindWindowEx(mainWindow, window, NULL, NULL);
	window = FindWindowEx(window2, NULL, NULL, NULL);
	window = FindWindowEx(window2, window, NULL, NULL);
	return window;
}

void MarioWindow::closeMarioApp()
{

	HWND window = ::FindWindow(L"WindowsForms10.Window.8.app.0.1e84ccb_r6_ad1", NULL);
	if (window!=NULL) {
		PostMessage(window, WM_CLOSE, 0, 0);
	}
	
}
