#pragma once
#include <array>
#include <vector>
#include "ActionEnum.h"

class AIAlgorithm;

class State
{
public:
	State();
	~State();
	Action getBestAction();
	double getValue(Action action);
	void setScore(Action action, double value);
	double getBestReward();
	void State::setPossibleActions(std::vector<Action> possibleActions);
private:
	std::vector<Action> possibleActions;
	std::array<double, (int)Action::ACTION_MAX> scores;
};

