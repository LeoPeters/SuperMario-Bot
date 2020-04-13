#pragma once
#include <windows.h>
class MarioWindow
{
public:
	static HWND getMarioWindow(LPCTSTR path);
	static HWND findMarioWindow();
	static void closeMarioApp();

};
