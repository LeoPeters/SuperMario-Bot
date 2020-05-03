#ifndef iagent_h
#define iagent_h
#include <vector>
#include <array>
#include "Globals.h"
#include "State.h"

class IMemory {
public:
	virtual void saveValues(std::array<std::vector<int>, NUMBER_OF_STATES> features) = 0;
	virtual void loadValues() = 0;
};
#endif
