#include "Globals.h"
#include "EnvironmentDummy.h"

void EnvironmentDummy::calculateStateAndActions(std::vector<std::vector<int>>, std::vector<MarioAction>* possibleActions, int* state)
{
	*state = rand() % (NUMBER_OF_STATES - 1);
	*possibleActions = { MarioAction::highJump, MarioAction::moveRight, MarioAction::jump };
}

void EnvironmentDummy::gameOver()
{
}
