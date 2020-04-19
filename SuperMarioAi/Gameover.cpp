#include <iostream>
#include <Windows.h>
#include <atlimage.h>
#include "Gameover.h"

using namespace std;
bool Gameover::isGameOver(HBITMAP hbitmap)
{
	CImage image;
	image.Attach(hbitmap);
	COLORREF j;
	RGBTRIPLE rgb;

	for (int i = 0; i < image.GetWidth();i++) {

		j=image.GetPixel( 150, image.GetHeight()/2);
		rgb.rgbtRed = GetRValue(j);
		rgb.rgbtGreen = GetGValue(j);
		rgb.rgbtBlue = GetBValue(j);
		printf("Red: %i | Green: %i | Blue: %i ", rgb.rgbtRed, rgb.rgbtGreen, rgb.rgbtBlue);
	}

		cout << endl;
	return false;
}
