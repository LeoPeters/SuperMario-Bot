#include "ScreenCaptureDummy.h"

void ScreenCaptureDummy::captureScreen(std::byte* image, int* lenght)
{
}

HBITMAP ScreenCaptureDummy::captureScreen(LPCTSTR fileName)
{
	return HBITMAP();
}

HBITMAP ScreenCaptureDummy::captureScreen()
{
	return HBITMAP();
}
