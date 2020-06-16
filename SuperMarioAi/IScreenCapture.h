#ifndef iscreencapture_h
#define iscreencapture_h
#include <windows.h>
#include <cstddef>
class IScreenCapture {
protected:
	IScreenCapture() {}
public:
	virtual ~IScreenCapture() {}
	virtual void captureScreen(std::byte* image, int* lenght)=0;
	virtual HBITMAP captureScreen(LPCTSTR fileName)=0;
	virtual HBITMAP captureScreen()=0;
	
};
#endif