#include "EnviromentDummy.h"

void EnviromentDummy::calculateStateAndActions(std::vector<std::vector<int>>, std::vector<action>* possibleActions, int* state)
{
	*state = rand()%300;
}

void EnviromentDummy::gameOver()
{
}
