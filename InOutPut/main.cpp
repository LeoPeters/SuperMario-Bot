#include <Windows.h>
#include "MarioWindow.h"
#include "ScreenCapture.h"
#include "Keyboard.h"
#include <iostream>
#include "main.h"
using namespace std;

int main() {
	HWND window = MarioWindow::getMarioWindow(L"C:/Users/Luisn/OneDrive/Desktop/Mesen.exe");
	Keyboard kb = Keyboard(window);
	ScreenCapture sc = ScreenCapture(window);
	sc.captureScreen(L"name.png");
	cout << "fui" << endl;
	kb.pressKey('d');
	kb.pressKey('d');
	kb.pressKey('d');
	kb.pressKey('d');
	kb.pressKey('d');
	char c = 's';
	do {
		std::cin >> c;
	} while (c != 'x');
}