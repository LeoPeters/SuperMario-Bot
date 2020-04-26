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
	std::cout << "BestAction: " << (int)best << "   Score: " << scores[(int)best] << std::endl;
	return best;
}
MarioAction State::getRandomAction() {
	if (possibleActions.size() <= 1) {
		return possibleActions[0];
	}
	MarioAction random = possibleActions[rand() % possibleActions.size()];

	return random;
}

MarioAction State::getRandomActionWeighted() {
	if (possibleActions.size() <= 1) {
		return possibleActions[0];
	}
	double rnd = std::rand() / (double)RAND_MAX;
	for (int i = 0; i < possibleActions.size(); i++) {
		if (rnd) {

		}
	}
	MarioAction random = possibleActions[rand() % (possibleActions.size() - 1)];

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