#pragma once

#include "MarioAction.h"
#include <Windows.h>
class IAppControl{
public:
	virtual void makeAction(marioAction) = 0;
	virtual void endGame()=0;
	virtual HWND startGame()=0;
	virtual void pauseGame()=0;
	virtual void unpauseGame()=0;
	virtual void restartGame()=0;
};