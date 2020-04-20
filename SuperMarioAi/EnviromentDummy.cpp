#include "Globals.h"
#include "EnvironmentDummy.h"

void EnvironmentDummy::calculateStateAndActions(std::vector<std::vector<int>>, std::vector<MarioAction>* possibleActions, int* state)
{
	*state = rand() % (NUMBER_OF_STATES - 1);
	*possibleActions = { MarioAction::highJump, MarioAction::moveRight, MarioAction::jump };
}

std::vector<int> EnvironmentDummy::getFeatureVector()
{
	return std::vector<int>();
}

std::array<std::vector<int>, NUMBER_OF_STATES> EnvironmentDummy::getStates() {
	return std::array<std::vector<int>, NUMBER_OF_STATES>();
}