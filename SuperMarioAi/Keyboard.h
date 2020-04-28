#ifndef _Keyboard_H
#define _Keyboard_H
class Keyboard
{
public:
	Keyboard(HWND window);
	void pressAndReleaseKey(char key, int pressDuration);
	void pressAndReleaseKey(char key, char key2, int pressDuration, int pressDuration2);
	void pressKey(char key);
	void releaseKey(char key);

private:
	bool windowIsFound = false;
	bool init(HWND window);
	HWND window;
	int GetKeyDownScanCode(char key);
	int GetKeyUpScanCode(char key);
};

#endif
