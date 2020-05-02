#ifndef iguiobserver_h
#define iguiobserver_h
#include "MarioAction.h"
#include "State.h"
#include "Globals.h"
#include "GameState.h"
class IGuiObserver {
public:	
	virtual void notifyStartPressed() = 0;
	virtual void notifyPausePressed() = 0;
	virtual void notifyEndApp() = 0;
	virtual std::vector<double> getQValues(int stateNumber)=0;
	virtual std::vector<int> getFeatureValues(int stateNumber)=0;
	virtual void loadMemory(std::string path)=0;

};
#endif