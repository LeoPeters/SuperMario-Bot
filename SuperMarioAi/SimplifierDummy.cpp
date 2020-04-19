#include "SimplifierDummy.h"
#include "Globals.h"



bool SimplifierDummy::simplifyImage(std::vector <std::vector<int>>* simply, HBITMAP image)
{

	int ergArray[GRIDRADIUS][GRIDRADIUS];
	for (int y = 0; y < GRIDRADIUS; y++) {
		for (int x = 0; x < GRIDRADIUS; x++) {
			if(simply->size()>0)
			ergArray[x][y]=simply->at(y).at(x);
		}
	}
	simply->clear();
	int status;
	env->environment_interface(PNG_NAME,ergArray,&status);
	for (int y = 0; y < GRIDRADIUS;y++) {
		std::vector<int> vecX;
		for (int x = 0; x < GRIDRADIUS; x++){
			vecX.push_back( ergArray[x][y]);
		}
		simply->push_back(vecX);
	}


	return status!=TOT;
}

void SimplifierDummy::init()
{
	env = new Environment();
}
