#include "ImageScanDummy.h"
#include "Globals.h"


ImageScanDummy::ImageScanDummy() {
}

static int ergArray[GRIDRADIUS][GRIDRADIUS];
static int done = 0;

bool ImageScanDummy::simplifyImage(std::vector <std::vector<int>>* simply, HBITMAP image)
{
	simply->clear();
	if (done == 0) {
		for (int y = 0; y < GRIDRADIUS; y++) {
			for (int x = 0; x < GRIDRADIUS; x++) {
				ergArray[x][y] = 0;
			}
		}
		done = 1;
	}

	env.environment_interface(PNG_NAME,ergArray);
	for (int y = 0; y < GRIDRADIUS;y++) {
		std::vector<int> vecX;
		for (int x = 0; x < GRIDRADIUS; x++){
			vecX.push_back( ergArray[x][y]);
		}
		simply->push_back(vecX);
	}
	return false;
}
