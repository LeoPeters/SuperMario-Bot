#include "SimplifierDummy.h"
#include "Globals.h"
#include <iostream>


GameState SimplifierDummy::simplifyImage(std::vector <std::vector<int>>* simply)
{
	GameState gameState;
	int ergArray[GRIDRADIUS][GRIDRADIUS];
	for (int y = 0; y < GRIDRADIUS; y++) {
		for (int x = 0; x < GRIDRADIUS; x++) {
			if(simply->size()>0)
			ergArray[x][y]=simply->at(y).at(x);
		}
	}
	simply->clear();
	int status=3;
	env->environment_interface(PNG_NAME,ergArray,&status);
	for (int y = 0; y < GRIDRADIUS;y++) {
		std::vector<int> vecX;
		for (int x = 0; x < GRIDRADIUS; x++){
			vecX.push_back( ergArray[x][y]);
		}
		simply->push_back(vecX);
	}
	switch (status) {
	case 0:
		gameState=GameState::MarioNotFound;

		break;
	case 1:
		gameState = GameState::Win;
		break;
	case 2:
		gameState = GameState::GameOver;
		break;
	case 3:
		gameState = GameState::MarioAlive;
		break;
	default:
		std::cout << "Default: " << status << std::endl;
		gameState = GameState::MarioNotFound;
	}

	return gameState;
}

void SimplifierDummy::init()
{
	env = new Environment();
}
