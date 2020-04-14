#ifndef environmentdummy_h
#define environmentdummy_h

#include "IEnviroment.h"

class EnviromentDummy:public IEnviroment
{

	 void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<marioAction>* possibleActions, int* state) override;
	 void gameOver() override;
};

#endif