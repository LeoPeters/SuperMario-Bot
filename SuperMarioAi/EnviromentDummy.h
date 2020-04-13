#pragma once
#include "IEnviroment.h"

class EnviromentDummy:public IEnviroment
{

	 void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<marioAction>* possibleActions, int* state) override;
	 void gameOver() override;
};

