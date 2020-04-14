#pragma once
#include <vector>
#include "ActionEnum.h"
class IEnvironment {
public:
	virtual void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<Action>* possibleActions,int* state) = 0;
	virtual void gameOver()=0;

};