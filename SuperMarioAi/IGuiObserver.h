#pragma once
class IGuiObserver {
public:	
	virtual void notifyStartPressed() = 0;
	virtual void notifyPausePressed() = 0;
	virtual void notifyEndApp() = 0;
};