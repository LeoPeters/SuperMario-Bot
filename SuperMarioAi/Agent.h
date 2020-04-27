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
	MarioAction calculateAction(int state, std::vector<MarioAction> possibleActions, double reward) override;
	virtual State Agent::getState(int index) override;

private:
	int lastState;
	double rewardRight;
	int counterRight;
	int counterLeft;
	Policy policy;
	MarioAction lastAction;
	std::array<State, NUMBER_OF_STATES> states;
	MarioAction chooseAction(State state);
};

