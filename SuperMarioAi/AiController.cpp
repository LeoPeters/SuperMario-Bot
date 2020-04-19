#include <vector>
#include <iostream>
#include "MarioWindow.h"
#include "Globals.h"
#include "AiController.h"

AiController::AiController(int argc, char** argv) :
	screenCapture(NULL),
	simplifier(NULL),
	features(NULL),
	agent(NULL),
	appControl(NULL),
	currentState(0),
	nextAction(MarioAction())
{
	gui = new AiGui(argc, argv, this);
}

void AiController::run() {
	bool playerAlive;



	while (isGuiRunning) {
		while (isGameStarted) {
			gameCapture = screenCapture->captureScreen(PNG_LNAME);
			if (!gui->getMainWindow()->getIsPaused()) {
				playerAlive=simplifier->simplifyImage(simplifyVec, gameCapture);
				if (playerAlive) {
				features->calculateStateAndActions(*simplifyVec, &possibleActions, &currentState);
				nextAction = agent->calculateAction(currentState, possibleActions);
				appControl->makeAction(nextAction);
				}
				else {
					features->gameOver();
					agent->gameOver();
					appControl->restartGame();
				}
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

MarioAction* AiController::getAction()
{
	return &nextAction;
}

std::vector<MarioAction>* AiController::getpossibleAction()
{
	return &possibleActions;
}

void AiController::startSuperMario()
{
	isGameStarted = false;
	if (factory.loadSuperMarioAi()) {
		this->screenCapture = factory.getScreenCapture();
		this->simplifier = factory.getImageScan();
		this->features = factory.getEnvironment();
		this->agent = factory.getAiAlgo();
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