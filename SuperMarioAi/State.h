#pragma once
#include <array>
#include <vector>
#include "MarioAction.h"

class Agent;

class State
{
public:
	State();
	~State();
	MarioAction getBestAction();
	double getValue(MarioAction action);
	void setScore(MarioAction action, double value);
	double getBestReward();
	void State::setPossibleActions(std::vector<MarioAction> possibleActions);
private:
	std::vector<MarioAction> possibleActions;
	std::array<double, (int)MarioAction::ACTION_MAX> scores;
};

