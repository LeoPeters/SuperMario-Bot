#include <vector>
#include <iostream>
#include "MarioWindow.h"
#include "Globals.h"
#include "AiController.h"

AiController::AiController(int argc, char** argv) :
	screenCapture(NULL),
	simplifier(NULL),
	enviroment(NULL),
	aiAlgo(NULL),
	appControl(NULL),
	currentState(0),
	nextAction(marioAction())
{
	gui = new AiGui(argc, argv, this);
}

void AiController::run() {
	bool playerAlive;

	std::vector<marioAction> possibleActions;

	while (isGuiRunning) {
		while (isGameStarted) {
			gameCapture = screenCapture->captureScreen(PNG_LNAME);
			if (!gui->getMainWindow()->getIsPaused()) {
				simplifier->simplifyImage(simplifyVec, gameCapture);
				enviroment->calculateStateAndActions(*simplifyVec, &possibleActions, &currentState);
				nextAction = aiAlgo->calculateAction(currentState, possibleActions);
				appControl->makeAction(nextAction);
			}
				gui->update();
		}
		Sleep(300);
	}
}

void AiController::runGui() {

	gui->runGui();
	isGuiRunning = false;
	isGameStarted = false;
}

void AiController::notifyPausePressed()
{
	if (appControl != NULL) {

		appControl->pauseGame();

	}
	else {
		std::cout << "No Window exists Please Start Game" << std::endl;
	}
}

void AiController::notifyStartPressed() {
	startSuperMario();
}

void AiController::notifyEndApp()
{
	gui->end();

}

int* AiController::getState()
{
	return &currentState;
}

std::vector<std::vector<int>>* AiController::getSimpleView()
{
	return simplifyVec;
}

HBITMAP* AiController::getGameView()
{
	return &gameCapture;
}

marioAction* AiController::getAction()
{
	return &nextAction;
}

void AiController::startSuperMario()
{
	isGameStarted = false;
	if (factory.loadSuperMarioAi()) {
		this->screenCapture = factory.getScreenCapture();
		this->simplifier = factory.getImageScan();
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