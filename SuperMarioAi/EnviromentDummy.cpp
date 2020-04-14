#include "EnviromentDummy.h"

void EnvironmentDummy::calculateStateAndActions(std::vector<std::vector<int>>, std::vector<Action>* possibleActions, int* state)
{
	*state = rand()%300;
}

void EnvironmentDummy::gameOver()
{
}
