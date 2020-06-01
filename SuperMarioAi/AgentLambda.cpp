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

std::vector<int> AgentLambda::getLambdaQueue()
{
	std::vector<int> lambdaQueue;
	for (auto it = lambdaTrace.crbegin(); it != lambdaTrace.crend(); ++it)
	{
		lambdaQueue.push_back(it->stateNumber);
	}
	return lambdaQueue;
}

MarioAction AgentLambda::calculateAction(int stateIndex, std::vector<MarioAction> possibleActions, double reward) {
	int tempIndex = stateIndex;
	states[stateIndex].setPossibleActions(possibleActions);

	if (stateIndex == 0) {
		tempIndex = lambdaTrace.front().stateNumber;
		lambdaTrace.pop_front();
	}
	int i = 0;
	//std::cout << "Loop" << std::endl;
	for (auto it = lambdaTrace.crbegin(); it != lambdaTrace.crend(); ++it) {
		double newScore = states[it->stateNumber].getValue(it->action) + ALPHA * (REWARDSTEP + reward + (GAMMA * states[tempIndex].getBestScore()) - states[lambdaTrace.front().stateNumber].getValue(lambdaTrace.front().action));
		states[it->stateNumber].setScore(it->action, newScore * pow(LAMBDAFACTOR, ++i));
		

		//std::cout << std::endl << "S: " << it->stateNumber << " A: " << it->action << "   ";
		//std::cout << "State: " << it->stateNumber << "Action: " << it->action << " " << newScore * pow(LAMBDAFACTOR, ++i) << " = " << states[it->stateNumber].getValue(it->action) << " + " << ALPHA << " * (" << REWARDSTEP << " + (" << GAMMA << " * " << states[tempIndex].getBestScore() << ") - " << states[lambdaTrace.front().stateNumber].getValue(lambdaTrace.front().action) << ")" << std::endl;
		//if (reward > 4 || reward < -4) {
		//	std::cout << "State: " << it->stateNumber << " Reward: " << (reward + REWARDSTEP) * pow(LAMBDAFACTOR, ++i) << std::endl;
		//}
	}
	//std::cout << std::endl;

	MarioAction action = chooseAction(states[stateIndex]);
	if (stateIndex == 0) {
		lambdaTrace.clear();
	} else 
	{
		if (lambdaTrace.size() == MAXQUEUESIZE)
		{
			lambdaTrace.pop_back();
		}
		lambdaTrace.push_front(LambdaEntry{ stateIndex, action });
	}

	return action;
}

MarioAction AgentLambda::chooseAction(State state) {
	double rnd = std::rand() / (double)RAND_MAX;
	MarioAction a = MarioAction::right;

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
	return a;
}