#pragma once
#include <vector>
#include "ActionEnum.h"
class IEnviroment {
public:
	virtual void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<action>* possibleActions,int* state) = 0;
	virtual void gameOver()=0;

};