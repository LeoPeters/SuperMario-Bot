#include "AIAlgorithm.h"

AIAlgorithm::AIAlgorithm() :
	lastState(0)
{

}

AIAlgorithm::~AIAlgorithm() {

}

Action AIAlgorithm::calculateAction(int stateIndex, std::vector<Action> possibleActions) {
	State state = states[stateIndex];
	state.setPossibleActions(possibleActions);
	Action action = chooseAction(state);






	double newScore = states[lastState].getValue(action);

		return action;
}

void AIAlgorithm::gameOver() {

}

Action AIAlgorithm::chooseAction(State state) {
	double rnd = std::rand() / RAND_MAX;
	Action a = Action::moveRight;

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
	}
	return a;
}

Action AIAlgorithm::getRandomAction() {
	return  (Action) (rand() % (int) Action::ACTION_MAX);
}