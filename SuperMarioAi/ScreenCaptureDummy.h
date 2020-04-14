#ifndef screencaptureDummy_h
#define screencaptureDummy_h
#include "IScreenCapture.h"
class ScreenCaptureDummy:public IScreenCapture
{
public:
	 void captureScreen(byte* image, int* lenght) override;
	 HBITMAP captureScreen(LPCTSTR fileName) override;
	 HBITMAP captureScreen() override;
};

#endif