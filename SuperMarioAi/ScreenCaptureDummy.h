#ifndef screencaptureDummy_h
#define screencaptureDummy_h
#include "IScreenCapture.h"
#include <cstddef>
class ScreenCaptureDummy:public IScreenCapture
{
public:
	 void captureScreen(std::byte* image, int* length) override;
	 HBITMAP captureScreen(LPCTSTR fileName) override;
	 HBITMAP captureScreen() override;
};

#endif