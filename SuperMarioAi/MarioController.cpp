#include "MarioController.h"
#include "KeyboardDefines.h"
#include "MarioWindow.h"
#include <iostream>
#define MAXJUMP_COUNT_RESET 3

MarioController::MarioController() :
	keyboard(NULL),
	window(NULL),
	keyboardThread(NULL)
{}


void MarioController::makeAction(MarioAction nextAction)
{

	static int jumpcounter = 0;

	isPressing = false;
	if (keyboardThread != NULL) {
		keyboardThread->join();
	}
	lastkeyBool = keyBool;
	for (int i = 0; i < keyBool.size(); i++) {
		keyBool[i] = false;
	}
	if (jumpcounter >= MAXJUMP_COUNT_RESET) {
		releaseAll();
		jumpcounter = 0;
		//Sleep(10);
	}
	switch (nextAction) {
	case MarioAction::right:
		jumpcounter = 0;
		keyBool[6] = true;
		break;
	case MarioAction::jumpRight:
		jumpcounter++;
		keyBool[6] = true;
		keyBool[3] = true;
		break;
	case MarioAction::left:
		jumpcounter = 0;
		keyBool[4] = true;
		break;
	case MarioAction::jumpLeft:
		jumpcounter++;
		keyBool[4] = true;
		keyBool[3] = true;
		break;
	case MarioAction::rightB:
		jumpcounter = 0;
		keyBool[6] = true;
		keyBool[1] = true;
		break;
	case MarioAction::jumpRightB:
		jumpcounter++;
		keyBool[6] = true;
		keyBool[3] = true;
		keyBool[1] = true;
		break;
	case MarioAction::leftB:
		jumpcounter = 0;
		keyBool[4] = true;
		keyBool[1] = true;
		break;
	case MarioAction::jumpLeftB:
		jumpcounter++;
		keyBool[4] = true;
		keyBool[1] = true;
		keyBool[3] = true;
		break;
	case MarioAction::jump:
		jumpcounter++;
		keyBool[3] = true;
		break;
	case MarioAction::B:
		jumpcounter = 0;
		keyBool[1] = true;
		break;
	case MarioAction::idle:
		jumpcounter = 0;
		break;
	case MarioAction::down:
		jumpcounter = 0;
		keyBool[2] = true;
		break;
	default:
		break;
	}
	isPressing = true;
	keyboardThread = new std::thread(&MarioController::pressKey, this);
	
}

void MarioController::endGame()
{
	MarioWindow::closeMarioApp();
}

HWND MarioController::startGame()
{
	window = MarioWindow::getMarioWindow(SUPER_MARIO_PATH);
	if (window == NULL) {
		std::cout << "Cant find Window: Please Close Super-Mario and press Restart" << std::endl;
		return NULL;
	}
	keyboard = new Keyboard(window);
	this->window = window;
	keyboard->pressAndReleaseKey(NUMPLUS, 120);
	keyboard->pressAndReleaseKey(NUMMUL, 120);
	keyboard->pressAndReleaseKey(NUMMIN, 120);
	Sleep(1000);
	isStarted = true;
	return window;
}

void MarioController::pauseGame()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUMMUL, 120);
		std::cout << "PressPause" << std::endl;
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::unpauseGame()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUMMUL, 120);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::restartGame()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUMMIN, 120);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

MarioController::~MarioController()
{
	endGame();
}


void MarioController::releaseAll() {
	for (int i = 0; i < keyBool.size(); i++) {
		if (!keyBool[i]&&lastkeyBool[i]) {
			keyboard->releaseKey(keyValue[i]);
			
		}
	}
}

void MarioController::pressKey()
{
	while (isPressing) {
		releaseAll();
		Sleep(4);
		for (int i = 0; i < keyBool.size(); i++) {
			if (keyBool[i]) {
				keyboard->pressKey(keyValue[i]);
			}
		}
	}
}