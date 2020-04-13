#pragma once
#include "IScreenCapture.h"
class ScreenCaptureDummy:public IScreenCapture
{
public:
	 void captureScreen(byte* image, int* lenght) override;
	 HBITMAP captureScreen(LPCTSTR fileName) override;
	 HBITMAP captureScreen() override;
};

