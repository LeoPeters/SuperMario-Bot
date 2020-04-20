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

Agent::~Agent() {

}

std::array<State, NUMBER_OF_STATES> Agent::getStates() {
	return states;
}

MarioAction Agent::calculateAction(int stateIndex, std::vector<MarioAction> possibleActions) {
	states[stateIndex].setPossibleActions(possibleActions);
	MarioAction action = chooseAction(states[stateIndex]);

	double newScore = states[lastState].getValue(action) +  ALPHA * (REWARDSTEP + rewardRight + GAMMA * states[stateIndex].getMaxReward() - states[lastState].getValue(action));
	states[lastState].setScore(lastAction, (states[lastState].getValue(lastAction) + newScore));
	lastAction = action;
	lastState = stateIndex;

	return action;
}

void Agent::gameOver() {
	states[lastState].setScore(lastAction, (states[lastState].getValue(lastAction) + REWARDLOSE));
	lastState = 0;
}



void Agent::gameWin() {
	states[lastState].setScore(lastAction, (states[lastState].getValue(lastAction) + REWARDWIN));
	lastState = 0;
}




MarioAction Agent::chooseAction(State state) {
	double rnd = std::rand() / (double) RAND_MAX;
	MarioAction a = MarioAction::moveRight;

	switch (policy) {
	case Policy::greedy:
		if (rnd <= EPSILON) {
			a = state.getRandomAction();
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
	printf("Rand: %f", rnd);
	std::cout << " Left: " << counterLeft << " Right: " << counterRight << std::endl;
	return a;
}