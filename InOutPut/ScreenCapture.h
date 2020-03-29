#ifndef _ScreenCapture_H
#define _ScreenCapture_H

class ScreenCapture {
public:
	ScreenCapture(HWND window);
	void captureScreen(byte* image, int* lenght);
	void captureScreen(LPCTSTR fileName);
private:
	HWND window;
	bool init(HWND window);
	HDC screenDevice;
	HDC imageDevice;
	HBITMAP image;
	bool windowIsFound = false;
	int screenWidth = 0;
	int screenHeight = 0;
};
#endif