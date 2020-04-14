#include "AiAlgoDummy.h"
#include <iostream>

Action AiAlgoDummy::calculateAction(int state, std::vector<Action> possibleActions)
{
	jumpcnt++;
	
		do {
			cnt2 = rand()%4;
		} while ((cnt2 == 2 || cnt2 == 3) && jumpcnt <= 15);

		cnt++;
		if (cnt2 == 2 || cnt2 == 3) {
			jumpcnt = 0;
		}
	return Action(cnt2);
}

void AiAlgoDummy::gameOver()
{
}
