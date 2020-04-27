#include "Globals.h"
#include "EnvironmentDummy.h"

void EnvironmentDummy::calculateStateAndActions(MarioAction nextAction, std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state, double* reward)
{
	*state = rand() % (NUMBER_OF_STATES - 1);
	*possibleActions = { MarioAction::highJump, MarioAction::moveRight, MarioAction::jump };
}

void EnvironmentDummy::gameWin() {

}

void EnvironmentDummy::gameOver() {

}

std::vector<int> EnvironmentDummy::getFeatureVector(int index)
{
	return std::vector<int>();
}

std::array<std::vector<int>, NUMBER_OF_STATES> EnvironmentDummy::getStates() {
	return std::array<std::vector<int>, NUMBER_OF_STATES>();
}