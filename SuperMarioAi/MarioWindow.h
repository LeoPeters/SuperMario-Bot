#ifndef mariowindow_h
#define mariowindow_h
#include <windows.h>
class MarioWindow
{
public:
	static HWND getMarioWindow(LPCTSTR path);
	static HWND findMarioWindow();
	static void closeMarioApp();

};
#endif
