#include "AgentDummy.h"
#include <iostream>
MarioAction AgentDummy::calculateAction(int state, std::vector<MarioAction> possibleActions)
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

void AgentDummy::gameOver()
{
}
