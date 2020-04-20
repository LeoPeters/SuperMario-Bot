#ifndef ienvironment_h
#define ienvironment_h
#include <vector>
#include <array>
#include "MarioAction.h"

class IEnvironment {
public:
	virtual void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<MarioAction>* possibleActions, int* state) = 0;
	virtual std::vector<int> getFeatureVector() = 0;
	virtual std::array<std::vector<int>, NUMBER_OF_STATES> getStates() = 0;
};
#endif