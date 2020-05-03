#ifndef ienvironment_h
#define ienvironment_h
#include <vector>
#include <array>
#include "MarioAction.h"

class IEnvironment {
public:
	virtual void calculateStateAndActions(MarioAction lastAction, std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state, double* reward) = 0;
	virtual std::vector<int> getFeatureVector(int i) = 0;
	virtual std::array<std::vector<int>, NUMBER_OF_STATES>* getStates() = 0;
	virtual void gameOver() = 0;
	virtual void gameWin() = 0;
	virtual int getStatesSize() = 0;
	virtual void setStatesSize(int statesSize) = 0;
};
#endif