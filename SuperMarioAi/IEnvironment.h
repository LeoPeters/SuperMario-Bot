#ifndef ienvironment_h
#define ienvironment_h
#include <vector>
#include "MarioAction.h"

class IEnvironment {
public:
	virtual void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<MarioAction>* possibleActions, int* state) = 0;
	virtual void gameOver()=0;
};
#endif