#ifndef environmentdummy_h
#define environmentdummy_h

#include "IEnvironment.h"

class EnvironmentDummy:public IEnvironment
{
public:
	 void calculateStateAndActions(std::vector<std::vector<int>>, std::vector<MarioAction>* possibleActions, int* state) override;
	 std::vector<int> getFeatureVector() override;
	 std::array<std::vector<int>, NUMBER_OF_STATES> getStates() override;
private:
	
};

#endif