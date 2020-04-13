#pragma once
#include "ActionEnum.h"
#include <vector>
class IAiAlgorithm {
public:
	virtual action calculateAction(int state,std::vector<action> possibleActions) = 0;
	virtual void gameOver() = 0;
};