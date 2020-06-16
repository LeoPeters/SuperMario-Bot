#ifndef _ScreenCapture_H
#define _ScreenCapture_H
#include "IScreenCapture.h"

class ScreenCapture: public IScreenCapture{
public:
	ScreenCapture(HWND window);
	 void captureScreen(std::byte* image, int* length) override;
	 HBITMAP captureScreen(LPCTSTR fileName) override;
	 HBITMAP captureScreen() override;
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