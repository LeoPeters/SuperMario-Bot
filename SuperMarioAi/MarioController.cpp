#include "MarioController.h"
#include "KeyboardDefines.h"
#include "Globals.h"
#include "MarioWindow.h"
#include <iostream>
MarioController::MarioController() :
	keyboard(NULL),
	window(NULL),
	keyboardThread(NULL)
{}

void MarioController::makeAction(MarioAction nextAction)
{
	if (keyboardThread != NULL) {
	keyboardThread->join();
	}
	switch (nextAction) {
	case MarioAction::moveLeft:
		keyboardThread= new std::thread(&MarioController::moveLeft,this);
		//moveLeft();
		break;
	case MarioAction::moveRight:
		keyboardThread = new std::thread(&MarioController::moveRight, this);
		//moveRight();
		break;
	case MarioAction::jump:
		//jump();
		keyboardThread = new std::thread(&MarioController::jump, this);
		break;
	case MarioAction::highJump:
		//highJump();
		keyboardThread = new std::thread(&MarioController::highJump, this);
		break;
	case MarioAction::shoot:
		//shoot();
		keyboardThread = new std::thread(&MarioController::shoot, this);
		break;
	}
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
	keyboard->pressAndReleaseKey(NUMPLUS, 100);
	keyboard->pressAndReleaseKey(NUMMUL, 100);
	keyboard->pressAndReleaseKey(NUMMIN, 100);
	Sleep(1000);
	isStarted = true;
	return window;
}

void MarioController::pauseGame()
{
	if (isStarted) {
			keyboard->pressAndReleaseKey(NUMMUL, 100);
			std::cout << "PressPause" << std::endl;
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::unpauseGame()
{
	if (isStarted) {
			keyboard->pressAndReleaseKey(NUMMUL, 100);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::restartGame()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUMMIN, 100);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

MarioController::~MarioController()
{
	endGame();
}

void MarioController::moveLeft()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM4, 150);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::moveRight()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM6, 150);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::jump()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM3, 100);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::highJump()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM3, 320);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::shoot()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM1, 150);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}