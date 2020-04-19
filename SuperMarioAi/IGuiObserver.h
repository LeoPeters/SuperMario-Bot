#ifndef iguiobserver_h
#define iguiobserver_h
#include "MarioAction.h"
class IGuiObserver {
public:	
	virtual void notifyStartPressed() = 0;
	virtual void notifyPausePressed() = 0;
	virtual void notifyEndApp() = 0;
	virtual int* getState() = 0;
	virtual std::vector <std::vector<int>>* getSimpleView()=0;
	virtual HBITMAP* getGameView() = 0;
	virtual MarioAction* getAction() = 0;
	virtual std::vector<MarioAction>* getpossibleAction() = 0;
};
#endif