#pragma once
#include <array>
#include <cstdlib>
#include <deque>
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
	State getState(int index) override;
	std::array<State, NUMBER_OF_STATES>* getStates() override;
	void setStates(std::array<State, NUMBER_OF_STATES> &states) override;

private:
	struct lambdaState {
		int stateNumber;
		MarioAction action;
	};

	int lastState;
	double rewardRight;
	Policy policy;
	std::deque<lambdaState> lambdaTrace;
	std::array<State, NUMBER_OF_STATES> states;
	MarioAction chooseAction(State state);
};

