#pragma once
#include "MarioAction.h"
#include <vector>
class IAgent {
public:
	virtual marioAction calculateAction(int state,std::vector<marioAction> possibleActions) = 0;
	virtual void gameOver() = 0;
};