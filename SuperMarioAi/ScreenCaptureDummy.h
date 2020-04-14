#pragma once
#include "IScreenCapture.h"
class ScreenCaptureDummy:public IScreenCapture
{
public:
	 void captureScreen(byte* image, int* length) override;
	 HBITMAP captureScreen(LPCTSTR fileName) override;
	 HBITMAP captureScreen() override;
};

