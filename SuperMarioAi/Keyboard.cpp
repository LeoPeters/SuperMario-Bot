#include <windows.h>
#include <iostream>
#include "Keyboard.h"
#include "KeyboardDefines.h"
#include <thread>
using namespace std;

void wait(int i) {
	for (int k = 0; 150 / 50; k++) {
		Sleep(50);
	}
}

Keyboard::Keyboard(HWND window) {
	init(window);
}

bool Keyboard::init(HWND window) {
	this->window = window;
	if (window != NULL) {
		windowIsFound = true;
	}
	return windowIsFound;
}

void Keyboard::pressAndReleaseKey(char key, int pressDuration) {
	if (windowIsFound) {
		if (pressDuration >= 50 && pressDuration <= 1800) {
			PostMessage(window, WM_ACTIVATE, 0x1, 0);
			int i = 0;
			while (i<pressDuration/10) {
				PostMessage(window, WM_KEYDOWN, NULL, GetKeyDownScanCode(key));
				Sleep(5);
				PostMessage(window, WM_CHAR, NULL, GetKeyDownScanCode(key));
				Sleep(5);
				i++;
			}
			//PostMessage(window, WM_KEYDOWN, NULL, GetKeyDownScanCode(key));
			//Sleep(pressDuration/3);
			//PostMessage(window, WM_CHAR, NULL, GetKeyDownScanCode(key));
			//Sleep(pressDuration / 3);
			//PostMessage(window, WM_CHAR, NULL, GetKeyDownScanCode(key));
			//Sleep(pressDuration / 3);

			for (int i = 0; i < 3; i++) {

				PostMessage(window, WM_KEYUP, NULL, GetKeyUpScanCode(key));
			}
		}
		else {
			cout << "The Press Duration must be between 100 and 500" << endl;
		}
	}
	else {
		cout << "Cant Press Button - Window doesn't exist!" << endl;
	}
}
void Keyboard::pressAndReleaseKey(char key, char key2, int pressDuration) {
	if (windowIsFound) {
			PostMessage(window, WM_ACTIVATE, 0x1, 0);
			int i = 0;
			int iMax = pressDuration / 20;
			while (i < iMax) {
				PostMessage(window, WM_KEYDOWN, NULL, GetKeyDownScanCode(key));
				Sleep(20);
				if (i > iMax * 0.5) {
					PostMessage(window, WM_KEYDOWN, NULL, GetKeyDownScanCode(key2));
				}
				i++;
			}
			//PostMessage(window, WM_KEYDOWN, NULL, GetKeyDownScanCode(key));
			//Sleep(pressDuration/3);
			//PostMessage(window, WM_CHAR, NULL, GetKeyDownScanCode(key));
			//Sleep(pressDuration / 3);
			//PostMessage(window, WM_CHAR, NULL, GetKeyDownScanCode(key));
			//Sleep(pressDuration / 3);
			for (int i = 0; i < 3; i++) {

			PostMessage(window, WM_KEYUP, NULL, GetKeyUpScanCode(key));
			PostMessage(window, WM_KEYUP, NULL, GetKeyUpScanCode(key2));
			Sleep(15);
			}
		}

	else {
		cout << "Cant Press Button - Window doesn't exist!" << endl;
	}
}
void Keyboard::pressKey(char key)
{
	if (windowIsFound) {
		PostMessage(window, WM_ACTIVATE, 0x1, 0);
		Sleep(25);
		PostMessage(window, WM_KEYDOWN, NULL, GetKeyDownScanCode(key));
		Sleep(25);
		PostMessage(window, WM_CHAR, NULL, GetKeyDownScanCode(key));

	}
	else {
		cout << "Cant Press Button - Window doesn't exist!" << endl;
	}
}
void Keyboard::releaseKey(char key)
{
	if (windowIsFound) {
		PostMessage(window, WM_ACTIVATE, 0x1, 0);
		Sleep(20);
		PostMessage(window, WM_KEYUP, NULL, GetKeyUpScanCode(key));
	}
	else {
		cout << "Cant Press Button - Window doesn't exist!" << endl;
	}
}



int Keyboard::GetKeyUpScanCode(char key) {
	return GetKeyDownScanCode(key) + 0xc000000;
}
int Keyboard::GetKeyDownScanCode(char key) {
	switch (key) {
	case 'Q':
	case 'q':
		return 0x00100001;
	case 'w':
	case 'W':
		return 0x00110001;
	case 'E':
	case 'e':
		return 0x120001;
	case 'r':
	case 'R':
		return 0x130001;
	case 'T':
	case 't':
		return 0x140001;
	case 'z':
	case 'Z':
		return 0x150001;
	case 'u':
	case 'U':
		return 0x160001;
	case 'i':
	case 'I':
		return 0x170001;
	case 'o':
	case 'O':
		return 0x180001;
	case 'p':
	case 'P':
		return 0x190001;
	case 'ü':
	case 'Ü':
		return 0x1A0001;
	case '+':
	case '*':
		return 0x1B0001;
	case 'a':
	case 'A':
		return 0x1E0001;
	case 's':
	case 'S':
		return 0x1F0001;
	case 'd':
	case 'D':
		return 0x200001;
	case 'f':
	case 'F':
		return 0x210001;
	case 'g':
	case 'G':
		return 0x220001;
	case 'h':
	case 'H':
		return 0x230001;
	case 'j':
	case 'J':
		return 0x240001;
	case 'k':
	case 'K':
		return 0x0250001;
	case 'l':
	case 'L':
		return 0x0260001;
	case 'ö':
	case 'Ö':
		return 0x0270001;
	case 'ä':
	case 'Ä':
		return 0x280001;
	case '#':
	case '\'':
		return 0x290001;
	case '<':
	case '>':
		return 0x560001;
	case 'y':
	case 'Y':
		return 0x2C0001;
	case 'x':
	case 'X':
		return 0x2D0001;
	case 'c':
	case 'C':
		return 0x2E0001;
	case 'v':
	case 'V':
		return 0x2F0001;
	case 'b':
	case 'B':
		return 0x300001;
	case 'n':
	case 'N':
		return 0x310001;
	case 'm':
	case 'M':
		return 0x320001;
	case ',':
	case ';':
		return 0x330001;
	case '.':
	case ':':
		return 0x340001;
	case '-':
	case '_':
		return 0x350001;
	case '^':
	case '°':
		return 0x290001;
	case '1':
	case '!':
		return 0x020001;
	case '2':
	case '"':
		return 0x030001;
	case '3':
	case '§':
		return 0x040001;
	case '4':
	case '$':
		return 0x050001;
	case '5':
	case '%':
		return 0x060001;
	case '6':
	case '&':
		return 0x070001;
	case '7':
	case '/':
		return 0x080001;
	case '8':
	case '(':
		return 0x090001;
	case '9':
	case ')':
		return 0x0A0001;
	case '0':
	case '=':
		return 0x0B0001;
	case 'ß':
	case '?':
		return 0x0C0001;
	case '´':
	case '`':
		return 0x0D0001;
	case ' ':
		return 0x390001;
	case NUM0:
		return 0x520001;
	case NUM1:
		return 0x4F0001;
	case NUM2:
		return 0x500001;
	case NUM3:
		return 0x510001;
	case NUM4:
		return 0x4B0001;
	case NUM5:
		return 0x4C0001;
	case NUM6:
		return 0x4D0001;
	case NUM7:
		return 0x470001;
	case NUM8:
		return 0x480001;
	case NUM9:
		return 0x490001;
	case NUMPLUS:
		return 0x4E0001;
	case NUMKOM:
		return 0x530001;
	case NUMMIN:
		return 0x4A0001;
	case NUMMUL:
		return 0x370001;
	case NUMDIV:
		return 0x1350001;
	default:
		return 0xAA0001;
	}
}