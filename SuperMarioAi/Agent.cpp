#include "Agent.h"

Agent::Agent() :
	lastState(0),
	policy(Policy::greedy),
	lastAction(MarioAction::moveLeft)
{

}

Agent::~Agent() {

}

MarioAction Agent::calculateAction(int stateIndex, std::vector<MarioAction> possibleActions) {
	State state = states[stateIndex];
	state.setPossibleActions(possibleActions);
	MarioAction action = chooseAction(state);
	
	double newScore = states[lastState].getValue(action) +  ALPHA * (REWARDSTEP + GAMMA * state.getMaxReward() - states[lastState].getValue(action));
	states[lastState].setScore(lastAction, newScore);

	lastAction = action;
	lastState = stateIndex;
	return action;
}

void Agent::gameOver() {
	
}



MarioAction Agent::chooseAction(State state) {
	double rnd = std::rand() / RAND_MAX;
	MarioAction a = MarioAction::moveRight;

	switch (policy) {
	case Policy::greedy:
		if (rnd <= EPSILON) {
			a = getRandomAction();
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

MarioAction Agent::getRandomAction() {
	return  (MarioAction) (rand() % ((int)MarioAction::ACTION_MAX - 1));
}