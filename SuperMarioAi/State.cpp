#include "State.h"

State::State() {
	for (auto i = 0; i < scores.size(); i++) {
		scores[i] = 0;
	}
}

State::~State() {

}

MarioAction State::getBestAction() {
	MarioAction best = possibleActions[0];
	for (auto i = 1; i < possibleActions.size(); i++) {
		if (scores[(int)possibleActions[i]] > scores[(int)best]) best = possibleActions[i];
	}
	return best;
}
MarioAction State::getRandomAction() {
	MarioAction random;
	int rnd= rand();
	int rndom;
	if (possibleActions.size()>0) {
		rndom =rnd% possibleActions.size();
			random= possibleActions[rndom]; //TODO: integer division by zero error
		}

	return random;
}

double State::getMaxReward() {
	double max = scores[0];
	for (auto i = 1; i < scores.size(); i++) {
		if (scores[i] > max) max = scores[i];
	}
	return max;
}

double State::getValue(MarioAction action) {
	return scores[(int)action];
}
void State::setScore(MarioAction action, double value) {
	scores[(int)action] = value;
}

void State::setPossibleActions(std::vector<MarioAction> possibleActions) {
	State::possibleActions = possibleActions;
}