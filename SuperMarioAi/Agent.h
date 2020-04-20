#pragma once
#include <array>
#include <cstdlib>
#include "Globals.h"
#include "IAgent.h"
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
	virtual std::array<State, NUMBER_OF_STATES> getStates() override;

private:
	int lastState;
	int rewardRight;
	int counterRight;
	int counterLeft;
	Policy policy;
	MarioAction lastAction;
	std::array<State, NUMBER_OF_STATES> states;
	MarioAction chooseAction(State state);
};

