#include "State.h"

State::State() {
	for (auto i = 0; i < scores.size(); i++) {
		scores[i] = 0;
	}
}

State::~State() {

}

Action State::getBestAction() {
	Action best = possibleActions[0];
	for (auto i = 1; i < possibleActions.size(); i++) {
		if (scores[(int)possibleActions[i]] > scores[(int)best]) best = possibleActions[i];
	}
	return best;
}

double State::getBestReward() {
	double max = scores[0];
	for (auto i = 1; i < scores.size(); i++) {
		if (scores[i] > max) max = scores[i];
	}
	return max;
}

double State::getValue(Action action) {
	return scores[(int)action];
}
void State::setScore(Action action, double value) {
	scores[(int)action] = value;
}

void State::setPossibleActions(std::vector<Action> possibleActions) {
	State::possibleActions = possibleActions;
}