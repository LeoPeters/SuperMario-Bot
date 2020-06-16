#include "AiControllerDQN.h"
#include <vector>
#include <iostream>
#include "MarioWindow.h"
#include "Globals.h"
#include "AiController.h"
#include "EnvironmentCalculation.h"
#include "AgentLambda.h"
#include "AgentDummy.h"

AiControllerDQN::AiControllerDQN(int argc, char** argv) :
	screenCapture(NULL),
	simplifier(NULL),

	appControl(NULL),
	numberOfCycles(0)
{
	data = new AiData();
	gui = new AiGui(argc, argv, this, data);

}

void AiControllerDQN::run() {
	while (isGuiRunning) {
		while (isGameStarted) {
			data->gameView = screenCapture->captureScreen(PNG_LNAME);
			if (!gui->getMainWindow()->getIsPaused()) {
				auto start = std::chrono::high_resolution_clock::now();
				data->lastAgentState = data->agentState;
				data->lastFeatureValues = data->featureValues;
				data->gameState = simplifier->simplifyImage(simplifyVec);
				auto stop = std::chrono::high_resolution_clock::now();
				switch (data->gameState) {
				case GameState::MarioAlive:
					data->loopCounter++;
					data->simpleView = *simplifyVec;

					appControl->makeAction(data->nextAction);
					break;
				case GameState::GameOver:
					numberOfCycles++;

					data->marioDeathCounter++;
					data->loopCounter++;


					appControl->restartGame();
					break;
				case GameState::Win:
					numberOfCycles++;
					data->marioWinCounter++;
					data->loopCounter++;

					appControl->restartGame();
					break;
				default:

					break;
				}
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
				auto fps = duration.count();
				data->loopTime = (int)fps;
			}
			gui->update();
		}
		Sleep(300);
	}
}

void AiControllerDQN::runGui() {
	gui->runGui();
	isGuiRunning = false;
	isGameStarted = false;
}

void AiControllerDQN::notifyPausePressed()
{
	if (appControl != NULL) {
		appControl->pauseGame();
	}
	else {
		std::cout << "No Window exists Please Start Game" << std::endl;
	}
}

void AiControllerDQN::notifyStartPressed() {
	startSuperMario();
}

void AiControllerDQN::notifyEndApp()
{
	gui->end();
}

void AiControllerDQN::startSuperMario()
{
	isGameStarted = false;
	if (factory.loadSuperMarioAi()) {
		this->screenCapture = factory.getScreenCapture();
		this->simplifier = factory.getImageScan();
		this->appControl = factory.getAppControl();
		this->screenCapture->captureScreen(PNG_LNAME);
		this->simplifier->init();
		isGameStarted = true;
		data->reset();
	}
}
std::vector<double> AiControllerDQN::getQValues(int stateNumber) {
	std::vector<double> qValues;

	return qValues;
}
std::vector<int> AiControllerDQN::getFeatureValues(int stateNumber) {
	std::vector<int> featureValues;
	return featureValues;
}

void AiControllerDQN::loadMemory(std::string path)
{
	SaveLoad* saveLoad = new SaveLoad();

	delete saveLoad;
}

void AiControllerDQN::saveMemory()
{

}

AiControllerDQN::~AiControllerDQN()
{
	if (appControl != NULL) {
		appControl->endGame();
	}
}