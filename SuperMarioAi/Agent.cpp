
#include "Agent.h"
#include <iostream>
Agent::Agent() :
	lastState(0),
	policy(Policy::greedy),
	lastAction(MarioAction::moveLeft),
	rewardRight(0),
	counterRight(0),
	counterLeft(0)
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

	double newScore = states[lastState].getValue(lastAction) + ALPHA * (REWARDSTEP + GAMMA * states[stateIndex].getMaxReward() - states[lastState].getValue(lastAction));
	//TODO reward zusätzlich summieren
	states[lastState].setScore(lastAction, newScore + reward);

	MarioAction action = chooseAction(states[stateIndex]);
	lastAction = action;
	lastState = stateIndex;

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
	if (a == MarioAction::moveRight) counterRight++;
	if (a == MarioAction::moveLeft) counterLeft++;
	
	//std::cout << " Left: " << counterLeft << " Right: " << counterRight << std::endl;
	return a;
}