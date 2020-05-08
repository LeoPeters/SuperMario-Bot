#include "AgentDummy.h"
#include <iostream>

MarioAction AgentDummy::calculateAction(int state, std::vector<MarioAction> possibleActions, double reward)
{
	MarioAction action;
	cnt++;
	if (cnt>actions.size()-1) {
		cnt = 0;
	}
	action = actions[cnt];
	//std::cout << action.toString() << std::endl;
	return action;
}

State AgentDummy::getState(int index)
{
	return State();
}

std::array<State, NUMBER_OF_STATES>* AgentDummy::getStates()
{

	return nullptr;
}

void AgentDummy::setStates(std::array<State, NUMBER_OF_STATES>& states)
{
}
