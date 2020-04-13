#pragma once
#include "IAppControl.h"
class AppControlDummy: public IAppControl
{
public:
	void makeAction(action) override;
	virtual void endGame() override;
	virtual HWND startGame() override;
	virtual void pauseGame() override;
	virtual void unpauseGame() override;
	virtual void restartGame() override;
};

