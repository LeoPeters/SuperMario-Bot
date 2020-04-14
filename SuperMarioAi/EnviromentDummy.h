#pragma once
#include "IEnvironment.h"

class EnvironmentDummy:public IEnvironment
{

	 void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<Action>* possibleActions, int* state) override;
	 void gameOver() override;
};

