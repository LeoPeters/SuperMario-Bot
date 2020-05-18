#include "AgentLambda.h"

#include "Agent.h"
#include <iostream>
#include <cmath> 
#include <ctgmath>
#include <deque>

AgentLambda::AgentLambda() :
	lastState(0),
	policy(Policy::greedy),
	rewardRight(0)
{

}

AgentLambda::~AgentLambda()
{

}

State AgentLambda::getState(int index)
{
	return states[index];
}

std::array<State, NUMBER_OF_STATES>* AgentLambda::getStates()
{
	return &states;
}

void AgentLambda::setStates(std::array<State, NUMBER_OF_STATES>& states)
{
	this->states = states;
}

MarioAction AgentLambda::calculateAction(int stateIndex, std::vector<MarioAction> possibleActions, double reward) {
	int tempIndex = stateIndex;
	states[stateIndex].setPossibleActions(possibleActions);
	 
	if (stateIndex == 0) {
		tempIndex = lambdaTrace.front().stateNumber;
		lambdaTrace.pop_front();
	}
	int i = 0;
	for (auto it = lambdaTrace.crbegin(); it != lambdaTrace.crend(); ++it) {
		//std::cout << std::endl << "State: " << it->stateNumber << " Action: " << it->action << std::endl;
		double newScore = states[it->stateNumber].getValue(it->action) + ALPHA * (REWARDSTEP + reward + GAMMA * states[tempIndex].getBestScore() - states[lambdaTrace.front().stateNumber].getValue(lambdaTrace.front().action));
		states[it->stateNumber].setScore(it->action, newScore * pow(LAMBDAFACTOR, ++i));
	}

	MarioAction action = chooseAction(states[stateIndex]);

	if (stateIndex == 0) {
		lambdaTrace.clear();
	}
	else 
	{
		if (lambdaTrace.size() > 0 && lambdaTrace.front().stateNumber == stateIndex && lambdaTrace.front().action == action)
		{
			return action;
		}
		if (lambdaTrace.size() == MAXQUEUESIZE)
		{
			lambdaTrace.pop_back();
		}
		lambdaTrace.push_front(lambdaState{ stateIndex, action });
	}
	for (int i = 0; i < MarioAction::size; i++) {
		std::cout << states[0].getValue(i) << ",";
	}
	std::cout << std::endl;
	return action;
}

MarioAction AgentLambda::chooseAction(State state) {
	double rnd = std::rand() / (double)RAND_MAX;
	MarioAction a = MarioAction::moveRight;

	switch (policy) {
	case Policy::greedy:
		if (rnd <= EPSILON) {
			a = state.getRandomAction();
			//printf("Rand: %f", rnd);
		}
		else {
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