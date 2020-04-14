#pragma once
#include <array>
#include <cstdlib>
#include "Globals.h"
#include "IAiAlgorithm.h"
#include "State.h"
#include "PolicyEnum.h"

class State;

class AIAlgorithm :public IAiAlgorithm
{
public:
	AIAlgorithm();
	~AIAlgorithm();

	Action calculateAction(int state, std::vector<Action> possibleActions) override;
	void gameOver() override;

private:
	int lastState;
	Policy policy;

	std::array<State, NUMBER_OF_STATES> states;
	Action chooseAction(State state);
	Action getRandomAction();

};

