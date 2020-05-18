#pragma once
#include <array>
#include <vector>
#include <iostream>
#include "MarioAction.h"

class Agent;

class State
{
public:
	State();
	~State();
	MarioAction getBestAction();
	MarioAction getRandomAction();
	MarioAction State::getRandomActionWeighted();
	double getValue(MarioAction action);
	void setScore(MarioAction action, double value);
	double getBestScore();
	void State::setPossibleActions(std::vector<MarioAction> possibleActions);

private:
	std::vector<MarioAction> possibleActions;
	std::array<double, MarioAction::size> scores;
};

