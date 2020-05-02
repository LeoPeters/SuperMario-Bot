#ifndef iscreencapture_h
#define iscreencapture_h
#include <windows.h>

class IScreenCapture {
protected:
	IScreenCapture() {}
public:
	virtual ~IScreenCapture() {}
	virtual void captureScreen(byte* image, int* lenght)=0;
	virtual HBITMAP captureScreen(LPCTSTR fileName)=0;
	virtual HBITMAP captureScreen()=0;
	
};
#endif