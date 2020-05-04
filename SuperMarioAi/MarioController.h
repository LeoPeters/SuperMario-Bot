#ifndef mariocontroller_h
#define mariocontroller_h
#include <windows.h>
#include "IAppControl.h"
#include "Keyboard.h"
#include <array>
#include <thread>
#include "Globals.h"
#include "KeyboardDefines.h"


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
	bool isPressing;
	HWND window;
	Keyboard* keyboard;
	void moveLeft();
	void moveRight();
	void jump();
	void highJump();
	void highJumpRight();
	void shoot();
	void releaseAll();
	void pressKey();
	std::array<bool, MAX_KEYBOARD_INPUTS> keyBool;
	std::array<char, MAX_KEYBOARD_INPUTS> keyValue = {NUM0,NUM1,NUM2 ,NUM3 ,NUM4 ,NUM5 ,NUM6 ,NUM7 ,NUM8 ,NUM9 };
	bool isPaused=true;
	bool isStarted = false;
	std::thread* keyboardThread;
	
};

#endif
