#include "AgentDummy.h"
#include <iostream>
MarioAction AgentDummy::calculateAction(int state, std::vector<MarioAction> possibleActions, double reward)
{
	jumpcnt++;
	
		do {
			cnt2 = rand()%4;
		} while ((cnt2 == 2 || cnt2 == 3) && jumpcnt <= 15);

		cnt++;
		if (cnt2 == 2 || cnt2 == 3) {
			jumpcnt = 0;
		}
	return MarioAction(cnt2);
}

State AgentDummy::getState(int index)
{
	return State();
}

std::array<State, NUMBER_OF_STATES> AgentDummy::getStates()
{
	return new ;
}

void AgentDummy::setStates(std::array<State, NUMBER_OF_STATES> &states) 
{

}