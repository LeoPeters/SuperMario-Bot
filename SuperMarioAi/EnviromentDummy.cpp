#include "EnvironmentDummy.h"

void EnvironmentDummy::calculateStateAndActions(std::vector<std::vector<int>>, std::vector<MarioAction>* possibleActions, int* state)
{
	*state = rand()%300;
}

void EnvironmentDummy::gameOver()
{
}
