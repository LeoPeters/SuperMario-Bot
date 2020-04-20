#ifndef iagent_h
#define iagent_h
#include "MarioAction.h"
#include <vector>
class IAgent {
public:
	virtual MarioAction calculateAction(int state,std::vector<MarioAction> possibleActions) = 0;
	virtual void gameOver() = 0;
	virtual void win() = 0;
};
#endif
