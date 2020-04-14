#ifndef environmentdummy_h
#define environmentdummy_h

#include "IEnvironment.h"

class EnvironmentDummy:public IEnvironment
{

	 void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<MarioAction>* possibleActions, int* state) override;
	 void gameOver() override;
};

#endif