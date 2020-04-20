#ifndef iagent_h
#define iagent_h
#include <vector>
#include <array>
#include "Globals.h"
#include "State.h"

class IAgent {
public:
	virtual MarioAction calculateAction(int state,std::vector<MarioAction> possibleActions) = 0;
	virtual void gameOver() = 0;
	virtual void gameWin() = 0;
	virtual std::array<State, NUMBER_OF_STATES> getStates() = 0;
};
#endif
