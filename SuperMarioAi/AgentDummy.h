#ifndef agentdummy_h
#define agentdummy_h
#include "IAgent.h"
class AgentDummy:public IAgent
{
public:
	 MarioAction calculateAction(int state, std::vector<MarioAction> possibleActions) override;
	 void gameOver() override;
	 void gameWin() override;
	 std::array<State, NUMBER_OF_STATES> getStates() override;
private:
	int cnt = 0;
	int cnt2 = 0;
	int jumpcnt = 0;
};
#endif

