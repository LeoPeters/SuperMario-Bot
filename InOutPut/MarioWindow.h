#pragma once
class MarioWindow
{
public:
	static HWND getMarioWindow(LPCTSTR path);
	static HWND findMarioWindow();
private:
	HWND window;
};
