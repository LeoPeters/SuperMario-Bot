#include "MarioController.h"
#include "KeyboardDefines.h"
#include "MarioWindow.h"
#include <iostream>
MarioController::MarioController() :
	keyboard(NULL),
	window(NULL),
	keyboardThread(NULL)
{}

void MarioController::makeAction(MarioAction nextAction)
{
	isPressing = false;
	if (keyboardThread != NULL) {
		keyboardThread->join();
	}
	for (int i = 0; i < keyBool.size(); i++) {
		keyBool[i] = false;
	}
	switch (nextAction) {
	case MarioAction::moveLeft:
		//keyboardThread= new std::thread(&MarioController::moveLeft,this);
		//moveLeft();
		keyBool[4] = true;
		break;
	case MarioAction::moveRight:
		//keyboardThread = new std::thread(&MarioController::moveRight, this);
		keyBool[6] = true;
		//moveRight();
		break;
	case MarioAction::jump:
		keyBool[3] = true;
		//jump();
		//keyboardThread = new std::thread(&MarioController::jump, this);

		break;
	case MarioAction::jumpRight:
		//highJump();
		keyBool[3] = true;
		keyBool[6] = true;
		//keyboardThread = new std::thread(&MarioController::highJump, this);
		//keyboardThread = new std::thread(&MarioController::highJumpRight, this);

		break;
	case MarioAction::shoot:
		//shoot();
		keyBool[1] = true;
		//keyboardThread = new std::thread(&MarioController::shoot, this);
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

void MarioController::moveLeft()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM4, 120);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::moveRight()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM6, 120);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::jump()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM3, 120);
		keyboard->pressAndReleaseKey(NUM6, 60);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::highJump()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM3, 520);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
}

void MarioController::highJumpRight()
{
	std::thread jump = std::thread(&MarioController::highJump, this);
	Sleep(380);
	keyboard->pressAndReleaseKey(NUM6, 120);
	jump.join();
}

void MarioController::shoot()
{
	if (isStarted) {
		keyboard->pressAndReleaseKey(NUM1, 60);
	}
	else {
		std::cout << "Game isn't started" << std::endl;
	}
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
	for (int i = 0; i < 4; i++) {
		releaseAll();
	
	}
	while (isPressing) {
		Sleep(15);
		for (int i = 0; i < keyBool.size(); i++) {
			if (keyBool[i]) {
				keyboard->pressKey(keyValue[i]);
			}
		}
		
	}
	lastkeyBool = keyBool;
}