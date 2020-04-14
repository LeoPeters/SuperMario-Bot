#pragma once
#include <array>
#include <cstdlib>
#include "Globals.h"
#include "IAgent.h"
#include "State.h"
#include "PolicyEnum.h"

class State;

class Agent :public IAgent
{
public:
	Agent();
	~Agent();

	MarioAction calculateAction(int state, std::vector<MarioAction> possibleActions) override;
	void gameOver() override;

private:
	int lastState;
	Policy policy;

	std::array<State, NUMBER_OF_STATES> states;
	MarioAction chooseAction(State state);
	MarioAction getRandomAction();

};

