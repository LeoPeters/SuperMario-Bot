
#include <iostream>
#include <string>
#include <windows.h>
#include <atlimage.h>
#include <chrono>
#include "ScreenCapture.h"

using namespace std;

ScreenCapture::ScreenCapture(HWND window) {
	init(window);
}

void ScreenCapture::captureScreen(byte* captureByte, int* ImageSize) {
	if (windowIsFound) {
		while (1) {
			using namespace Gdiplus;
			int waitingTime;
			IStream* stream = nullptr;
			CreateStreamOnHGlobal(NULL, TRUE, &stream);
			BitBlt(imageDevice, 0, 0, screenWidth, screenHeight, screenDevice, 0, 0, SRCCOPY);
			CImage cimage;
			cimage.Attach(image);
			cimage.Save(stream, ImageFormatPNG);
			HGLOBAL hg = NULL;
			GetHGlobalFromStream(stream, &hg);
			*ImageSize = GlobalSize(hg);
			LPVOID pimage = GlobalLock(hg);
			captureByte = (byte*)malloc(*ImageSize);
			memcpy(captureByte, pimage, *ImageSize);
			GlobalUnlock(hg);
			stream->Release();
			//auto start = std::chrono::high_resolution_clock::now();
			//auto stop = std::chrono::high_resolution_clock::now();
			//auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
			//auto fps = duration.count();
			//printf("FPS: %d !\n", 1000000 / (int)fps);
		}
	}
	else {
		cout << "Cant Capture Image - No window exist" << endl;
	}
}
HBITMAP ScreenCapture::captureScreen() {
	BitBlt(imageDevice, 0, 0, screenWidth, screenHeight, screenDevice, 0, 0, SRCCOPY);
	return image;
}
HBITMAP ScreenCapture::captureScreen(LPCTSTR fileName) {
	if (windowIsFound) {
		using namespace Gdiplus;
		//auto start = std::chrono::high_resolution_clock::now();
		BitBlt(imageDevice, 0, 0, screenWidth, screenHeight, screenDevice, 0, 0, SRCCOPY);
		CImage cimage;
		cimage.Attach(image);
		cimage.Save(fileName, ImageFormatPNG);
		//auto stop = std::chrono::high_resolution_clock::now();
		//auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		//auto fps = duration.count();
		//printf("FPS: %d !\n", 1000000 / (int)fps);
	}
	else {
		cout << "Can't Capture Image - window  doesn't exist" << endl;
	}
	return image;
}

bool ScreenCapture::init(HWND window) {
	this->window = window;
	if (window != NULL) {
		windowIsFound = true;
		RECT rect;
		GetWindowRect(window, &rect);
		screenWidth = (int)((rect.right - rect.left));
		screenHeight = (int)((rect.bottom - rect.top));
		screenDevice = GetWindowDC(window);
		imageDevice = CreateCompatibleDC(screenDevice);
		image = CreateCompatibleBitmap(screenDevice, screenWidth, screenHeight);
		SelectObject(imageDevice, image);
	}
	return windowIsFound;
}