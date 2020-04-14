#ifndef agentdummy_h
#define agentdummy_h
#include "IAgent.h"
class AgentDummy:public IAgent
{
public:
	 marioAction calculateAction(int state, std::vector<marioAction> possibleActions) override;
	 void gameOver() override;
private:
	int cnt = 0;
	int cnt2 = 0;
	int jumpcnt = 0;
};
#endif

