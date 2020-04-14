#pragma once

#include "ActionEnum.h"
#include <Windows.h>
class IAppControl{
public:
	virtual void makeAction(Action) = 0;
	virtual void endGame()=0;
	virtual HWND startGame()=0;
	virtual void pauseGame()=0;
	virtual void unpauseGame()=0;
	virtual void restartGame()=0;
};