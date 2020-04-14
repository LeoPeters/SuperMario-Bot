#ifndef appcontrolldummy_h
#define appcontrolldummy_h

#include "IAppControl.h"
class AppControlDummy: public IAppControl
{
public:
	void makeAction(marioAction) override;
	virtual void endGame() override;
	virtual HWND startGame() override;
	virtual void pauseGame() override;
	virtual void unpauseGame() override;
	virtual void restartGame() override;
};

#endif