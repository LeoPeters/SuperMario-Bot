#include "Agent.h"
#include <iostream>
Agent::Agent() :
	lastState(0),
	policy(Policy::greedy),
	lastAction(MarioAction::moveLeft)
{

}

Agent::~Agent() {

}

MarioAction Agent::calculateAction(int stateIndex, std::vector<MarioAction> possibleActions) {
	states[stateIndex].setPossibleActions(possibleActions);
	MarioAction action = chooseAction(states[stateIndex]);
	
	double newScore = states[lastState].getValue(action) +  ALPHA * (REWARDSTEP + GAMMA * states[stateIndex].getMaxReward() - states[lastState].getValue(action));
	states[lastState].setScore(lastAction, newScore);

	lastAction = action;
	lastState = stateIndex;

	for (int i = 0; i < possibleActions.size(); i++) {
		if ((int)possibleActions[i] == 0) std::cout << "moveLeft" << std::endl;
		if ((int)possibleActions[i] == 1) std::cout << "moveRight" << std::endl;
		if ((int)possibleActions[i] == 2) std::cout << "jump" << std::endl;
		if ((int)possibleActions[i] == 3) std::cout << "highJump" << std::endl;
		if ((int)possibleActions[i] == 4) std::cout << "shoot" << std::endl;
	}

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