#pragma once
#include "IAiAlgorithm.h"

class AiAlgoDummy:public IAiAlgorithm
{
public:
	 Action calculateAction(int state, std::vector<Action> possibleActions) override;
	 void gameOver() override;
private:
	int cnt = 0;
	int cnt2 = 0;
	int jumpcnt = 0;
};

