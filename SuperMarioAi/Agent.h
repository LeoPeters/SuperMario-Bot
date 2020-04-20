#pragma once
#include <array>
#include <cstdlib>
#include "Globals.h"
#include "IAgent.h"
#include "State.h"
#include "Policy.h"
#include "MarioAction.h"

class State;

class Agent : public IAgent
{
public:
	Agent();
	~Agent();

	MarioAction calculateAction(int state, std::vector<MarioAction> possibleActions) override;
	void gameOver() override;
	void gameWin() override;

private:
	int lastState;
	int rewardRight;
	Policy policy;
	MarioAction lastAction;
	std::array<State, NUMBER_OF_STATES> states;
	MarioAction chooseAction(State state);
};

