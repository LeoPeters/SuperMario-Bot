#pragma once
#include "ActionEnum.h"
#include <vector>
class IAiAlgorithm {
public:
	virtual Action calculateAction(int state,std::vector<Action> possibleActions) = 0;
	virtual void gameOver() = 0;
};