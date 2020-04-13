#include "AiAlgoDummy.h"
#include <iostream>
action AiAlgoDummy::calculateAction(int state, std::vector<action> possibleActions)
{
	jumpcnt++;
	
		do {
			cnt2 = rand()%4;
		} while ((cnt2 == 2 || cnt2 == 3) && jumpcnt <= 15);

		cnt++;
		if (cnt2 == 2 || cnt2 == 3) {
			jumpcnt = 0;
		}
	return action(cnt2);
}

void AiAlgoDummy::gameOver()
{
}
