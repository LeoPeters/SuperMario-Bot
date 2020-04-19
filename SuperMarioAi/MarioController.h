#ifndef mariocontroller_h
#define mariocontroller_h
#include <windows.h>
#include "IAppControl.h"
#include "Keyboard.h"
#include <thread>



class MarioController: public IAppControl
{
public:
	MarioController();
	void makeAction(MarioAction nextAction) override;

	void endGame() override;
	HWND startGame() override;
	void pauseGame() override;
	void unpauseGame() override;
	void restartGame() override;
	~MarioController();
private:
	HWND window;
	Keyboard* keyboard;
	void moveLeft();
	void moveRight();
	void jump();
	void highJump();
	void shoot();
	bool isPaused=true;
	bool isStarted = false;
	std::thread* keyboardThread;
	
};

#endif
