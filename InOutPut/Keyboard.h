#ifndef _Keyboard_H
#define _Keyboard_H
class Keyboard
{
public:
	Keyboard(HWND window);
	void pressKey(char key);

private:
	bool windowIsFound = false;
	bool init(HWND window);
	HWND window;
	int GetKeyDownScanCode(char key);
	int GetKeyUpScanCode(char key);
};

#endif
