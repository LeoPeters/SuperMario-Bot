#ifndef environmentdummy_h
#define environmentdummy_h

#include "IEnvironment.h"
#include "MarioFeature.h"
class EnvironmentDummy:public IEnvironment
{
public:
	 void calculateStateAndActions(MarioAction lastAction, std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state, double* reward) override;
	 std::vector<int> getFeatureVector(int index) override;
	 std::array<std::vector<int>, NUMBER_OF_STATES>* getStates() override;
	 void gameOver() override;
	 void gameWin() override;
	 int getStatesSize() override;
	 void setStatesSize(int statesSize) override;
	 void setActiveFeatures(std::vector<MarioFeature> activeFeatures) override;
private:
	
};

#endif