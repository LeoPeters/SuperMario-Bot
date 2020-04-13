#pragma once
#include <vector>
#include "MarioAction.h"
class IEnviroment {
public:
	virtual void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<marioAction>* possibleActions,int* state) = 0;
	virtual void gameOver()=0;

};