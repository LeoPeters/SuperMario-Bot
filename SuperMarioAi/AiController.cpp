#include <vector>
#include <iostream>
#include "MarioWindow.h"
#include "Globals.h"
#include "AiController.h"

AiController::AiController(int argc, char** argv) :
	screenCapture(NULL),
	imageScan(NULL),
	enviroment(NULL),
	aiAlgo(NULL),
	appControl(NULL),
	currentState(0),
	nextAction(action())
{
	gui = new AiGui(argc, argv, this);
}

void AiController::run() {
	bool playerAlive;

	std::vector<action> possibleActions;

	while (gui->mainWindowIsVisible()) {
		while (isGameStarted) {
  
			gameCapture = screenCapture->captureScreen(PNG_LNAME);
			if (!gui->isPaused()) {
				imageScan->simplifyImage(simplifyVec, gameCapture);
				enviroment->calculateStateAndActions(*simplifyVec, &possibleActions, &currentState);
				//nextAction = aiAlgo->calculateAction(currentState, possibleActions);
				//appControl->makeAction(nextAction);
			}
		}
		if (isGameStarted) {
			std::unique_lock<std::mutex> lock(mx);
			cv.wait(lock);
		}
	}
}

void AiController::runGui() {
	while (gui->mainWindowIsVisible()) {
		gui->update(gameCapture, *simplifyVec, nextAction,currentState);
		Sleep(10);
	}
	isGameStarted = false;
	cv.notify_all();
}

void AiController::notifyPausePressed()
{
	if (appControl != NULL) {
		std::lock_guard<std::mutex> lg(mx);
		appControl->pauseGame();
		cv.notify_all();
	}
	else {
		std::cout << "No Window exists Please Start Game" << std::endl;
	}
}

void AiController::notifyStartPressed() {
	std::lock_guard<std::mutex> lg(mx);
	startSuperMario();
	cv.notify_all();
}

void AiController::notifyEndApp()
{
	isGameStarted = false;
	cv.notify_all();
}

void AiController::startSuperMario()
{
	isGameStarted = false;
		if (factory.loadSuperMarioAi()) {
			this->screenCapture = factory.getScreenCapture();
			this->imageScan = factory.getImageScan();
			this->enviroment = factory.getEnviroment();
			this->aiAlgo = factory.getAiAlgo();
			this->appControl = factory.getAppControl();
			isGameStarted = true;
		}	
	}


AiController::~AiController()
{
	if (appControl != NULL) {
		appControl->endGame();
	}
}