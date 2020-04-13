#include "EnviromentDummy.h"

void EnviromentDummy::calculateStateAndActions(std::vector<std::vector<int>>, std::vector<marioAction>* possibleActions, int* state)
{
	*state = rand()%300;
}

void EnviromentDummy::gameOver()
{
}
