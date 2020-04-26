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



	while (isGuiRunning) {
		while (isGameStarted) {
		gameCapture = screenCapture->captureScreen(PNG_LNAME);
			
			if (!gui->getMainWindow()->getIsPaused()) {
				gameState=simplifier->simplifyImage(simplifyVec, gameCapture);
				switch (gameState) {
				case GameState::MarioAlive:
					features->calculateStateAndActions(*simplifyVec, &possibleActions, &currentState);
					featureVector = features->getFeatureVector();
					nextAction = agent->calculateAction(currentState, possibleActions);
					agentStateArray = agent->getStates();
					appControl->makeAction(nextAction);
					break;
				case GameState::GameOver:
					agent->gameOver();
					appControl->restartGame();
					break;
				case GameState::Win:
					agent->gameWin();
					appControl->restartGame();
					break;
				default:
					break;
				}
				gui->update();
			}

		}
		Sleep(200);
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

int AiController::getState()
{
	return currentState;
}

std::vector<std::vector<int>> AiController::getSimpleView()
{
	return *simplifyVec;
}

HBITMAP AiController::getGameView()
{
	return gameCapture;
}

MarioAction AiController::getAction()
{
	return nextAction;
}

std::vector<MarioAction> AiController::getpossibleAction()
{
	return possibleActions;
}

std::vector<int> AiController::getFeatureVector()
{
	return featureVector;
}

GameState AiController::getGameState()
{
	return gameState;
}

std::array<State, NUMBER_OF_STATES>AiController::getAgentStateList()
{

	return agentStateArray;
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
		this->screenCapture->captureScreen(PNG_LNAME);
		this->simplifier->init();
		isGameStarted = true;
	}
}

AiController::~AiController()
{
	if (appControl != NULL) {
		appControl->endGame();
	}
}