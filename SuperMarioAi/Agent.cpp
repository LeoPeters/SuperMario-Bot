
#include "Agent.h"
#include <iostream>
#include <cmath> 
#include <ctgmath>
#include <deque>

Agent::Agent() :
	lastState(0),
	policy(Policy::greedy),
	rewardRight(0)
{
	
}

Agent::~Agent() 
{

}

State Agent::getState(int index) 
{
	return states[index];
}

std::array<State, NUMBER_OF_STATES>* Agent::getStates()
{
	return &states;
} 

void Agent::setStates(std::array<State, NUMBER_OF_STATES> &states)
{
	this->states = states;
}

MarioAction Agent::calculateAction(int stateIndex, std::vector<MarioAction> possibleActions, double reward) {
	states[stateIndex].setPossibleActions(possibleActions);

	std::cout << "Size: " << lambdaTrace.size() << std::endl;
	int i = 0;
	for (auto it = lambdaTrace.crbegin(); it != lambdaTrace.crend(); ++it) {
		//std::cout << std::endl << "State: " << it->stateNumber << " Action: " << it->action << std::endl;
		double newScore = states[it->stateNumber].getValue(it->action) + ALPHA * (REWARDSTEP + reward + GAMMA * states[stateIndex].getMaxReward() - states[lambdaTrace.front().stateNumber].getValue(lambdaTrace.front().action));
		states[it->stateNumber].setScore(it->action, newScore * pow(LAMBDAFACTOR, ++i));
	}

	MarioAction action = chooseAction(states[stateIndex]);

	if (stateIndex == 0) {
		lambdaTrace.clear();
	} else
	{
		for (auto it = lambdaTrace.begin(); it != lambdaTrace.end(); ++it) 
		{
			if (it->stateNumber == stateIndex && it->action == action) 
			{
				return action;
			}
		}
		if (lambdaTrace.size() == MAXQUEUESIZE) 
		{
			lambdaTrace.pop_back();
		}
		lambdaTrace.push_front(lambdaState{ stateIndex, action });
	}
	return action;
}

MarioAction Agent::chooseAction(State state) {
	double rnd = std::rand() / (double) RAND_MAX;
	MarioAction a = MarioAction::moveRight;

	switch (policy) {
	case Policy::greedy:
		if (rnd <= EPSILON) {
			a = state.getRandomAction();
			//printf("Rand: %f", rnd);
		} else {
			a = state.getBestAction();
		}
		break;
	case Policy::soft:
		if (rnd <= 1 - EPSILON) {
			a = state.getBestAction();
		}
		else {
			a = state.getRandomAction();
		}
		break;
	case Policy::softMax:
		if (rnd <= 1 - EPSILON) {
			a = state.getBestAction();
		}
		else {
			a = state.getRandomActionWeighted(); //TODO get random action Weighted implementing
		}
		break;
	}
	if (state.getBestAction() != a) {
		lambdaTrace.clear();
	}
	
	//std::cout << " Left: " << counterLeft << " Right: " << counterRight << std::endl;
	return a;
}