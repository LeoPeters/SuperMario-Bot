#ifndef iappcontrol_h
#define iappcontrol_h

#include "MarioAction.h"
#include <Windows.h>
class IAppControl{
public:
	virtual void makeAction(MarioAction) = 0;
	virtual void endGame()=0;
	virtual HWND startGame()=0;
	virtual void pauseGame()=0;
	virtual void unpauseGame()=0;
	virtual void restartGame()=0;
};
#endif
