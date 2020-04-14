#include "EnvironmentDummy.h"

void EnvironmentDummy::calculateStateAndActions(std::vector<std::vector<int>>, std::vector<marioAction>* possibleActions, int* state)
{
	*state = rand()%300;
}

void EnvironmentDummy::gameOver()
{
}
