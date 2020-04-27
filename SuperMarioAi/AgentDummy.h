#ifndef agentdummy_h
#define agentdummy_h
#include "IAgent.h"
class AgentDummy:public IAgent
{
public:
	 MarioAction calculateAction(int state, std::vector<MarioAction> possibleActions, double reward) override;
	 State getState(int index) override;
private:
	int cnt = 0;
	int cnt2 = 0;
	int jumpcnt = 0;
};
#endif

