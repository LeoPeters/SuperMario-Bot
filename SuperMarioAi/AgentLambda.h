#pragma once
#include <array>
#include <cstdlib>
#include <deque>
#include "Globals.h"
#include "IAgent.h"
#include "Policy.h"
#include "MarioAction.h"

class State;

class AgentLambda : public IAgent
{
public:
	struct LambdaEntry {
		int stateNumber;
		MarioAction action;
	};
	AgentLambda();
	~AgentLambda();
	MarioAction calculateAction(int state, std::vector<MarioAction> possibleActions, double reward) override;
	State getState(int index) override;
	std::array<State, NUMBER_OF_STATES>* getStates() override;
	void setStates(std::array<State, NUMBER_OF_STATES>& states) override;
	std::vector<int> getLambdaQueue() override;

private:
	int lastState;
	double rewardRight;
	Policy policy;
	std::deque<LambdaEntry> lambdaTrace;
	std::array<State, NUMBER_OF_STATES> states;

	MarioAction chooseAction(State state);
};

