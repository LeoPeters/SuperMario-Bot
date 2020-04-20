#include "Agent.h"
#include <iostream>
Agent::Agent() :
	lastState(0),
	policy(Policy::greedy),
	lastAction(MarioAction::moveLeft),
	rewardRight(0)
{

}

Agent::~Agent() {

}

MarioAction Agent::calculateAction(int stateIndex, std::vector<MarioAction> possibleActions) {
	states[stateIndex].setPossibleActions(possibleActions);
	MarioAction action = chooseAction(states[stateIndex]);
	//rewardRight = (lastAction == MarioAction::moveRight) ? 10 : 0;

	double newScore = states[lastState].getValue(action) +  ALPHA * (REWARDSTEP + rewardRight + GAMMA * states[stateIndex].getMaxReward() - states[lastState].getValue(action));
	states[lastState].setScore(lastAction, (states[lastState].getValue(lastAction) + newScore));
	//std::cout << "Set new Score: " << states[lastState].getValue(lastAction) << std::endl;
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
	double rnd = std::rand() / RAND_MAX;
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
		
		break;
	case Policy::softMax:
		break;
	}
	return a;
}