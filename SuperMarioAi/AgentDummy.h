#ifndef agentdummy_h
#define agentdummy_h
#include "IAgent.h"
#include "MarioAction.h"
class AgentDummy:public IAgent
{
public:
	 MarioAction calculateAction(int state, std::vector<MarioAction> possibleActions, double reward) override;
	 State getState(int index) override;
	 std::array<State, NUMBER_OF_STATES>* getStates()override;
	 void setStates(std::array<State, NUMBER_OF_STATES>& states) override;
private:
	int cnt = 0;
	std::array<MarioAction, 6> actions = {MarioAction::jump,MarioAction::jump,MarioAction::jumpRight,MarioAction::moveRight,MarioAction::moveLeft,MarioAction::moveRight };
};


#endif

