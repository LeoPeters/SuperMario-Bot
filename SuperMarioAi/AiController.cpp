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
	appControl(NULL)

{
	gui = new AiGui(argc, argv, this);
	data = gui->getData();
}

void AiController::run() {
	while (isGuiRunning) {
		while (isGameStarted) {
			data->setGameView(screenCapture->captureScreen(PNG_LNAME));

			auto start = std::chrono::high_resolution_clock::now();
			if (!gui->getMainWindow()->getIsPaused()) {
				data->gameState = simplifier->simplifyImage(simplifyVec);
				switch (data->gameState) {
				case GameState::MarioAlive:
					data->loopCounter++;
					data->setSimpleView(*simplifyVec);
					features->calculateStateAndActions(data->nextAction, *simplifyVec, &data->possibleActions, &data->agentStateNumber, &reward);
					//std::cout << "Reward: " << reward << std::endl;
					data->nextAction = agent->calculateAction(data->agentStateNumber, data->possibleActions, reward);
					data->agentState = agent->getState(data->agentStateNumber);
					appControl->makeAction(data->nextAction);
					break;
				case GameState::GameOver:
					data->marioDeathCounter++;
					data->loopCounter++;
					features->gameOver();
					features->calculateStateAndActions(data->nextAction, *simplifyVec, &data->possibleActions, &data->agentStateNumber, &reward);
					agent->calculateAction(data->agentStateNumber, data->possibleActions, reward);
					appControl->restartGame();
					break;
				case GameState::Win:
					data->marioWinCounter++;
					data->loopCounter++;
					features->gameWin();
					features->calculateStateAndActions(data->nextAction, *simplifyVec, &data->possibleActions, &data->agentStateNumber, &reward);
					agent->calculateAction(data->agentStateNumber, data->possibleActions, reward);
					appControl->restartGame();
					break;
				default:
					break;
				}
			}
			data->featureValues = features->getFeatureVector(data->agentStateNumber);
			auto stop = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			auto fps = duration.count();
			data->loopTime = (int)fps;
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
		data->reset();
	}
}
std::vector<double> AiController::getQValues(int stateNumber) {
	std::vector<double> qValues;
	if (agent != NULL) {
		State state=agent->getState(stateNumber);
		for (int i = 0; i < MarioAction::size; i++) {
			qValues.push_back(state.getValue(i));
		}
	}
	return qValues;
}
std::vector<int> AiController::getFeatureValues(int stateNumber) {
	std::vector<int> featureValues;
	if (features != NULL) {
		featureValues=features->getFeatureVector(stateNumber);
	}
	return featureValues;
}

void AiController::loadMemory(std::string path)
{
	std::cout << path << std::endl;
}

AiController::~AiController()
{
	if (appControl != NULL) {
		appControl->endGame();
	}
}