#include <vector>
#include <iostream>
#include "MarioWindow.h"
#include "Globals.h"
#include "AiController.h"
#include "EnvironmentCalculation.h"
#include "Agent.h"

AiController::AiController(int argc, char** argv) :
	screenCapture(NULL),
	simplifier(NULL),
	environment(NULL),
	agent(NULL),
	appControl(NULL),
	numberOfCycles(0)
{
	agent = new Agent();
	environment = new EnvironmentCalculation();
	gui = new AiGui(argc, argv, this);
	data = gui->getData();
}

void AiController::run() {

	while (isGuiRunning) {
		while (isGameStarted) {
			data->setGameView(screenCapture->captureScreen(PNG_LNAME));

			auto start = std::chrono::high_resolution_clock::now();
			if (!gui->getMainWindow()->getIsPaused()) {
				data->lastAgentState = data->agentState;
				data->lastFeatureValues = data->featureValues;
				data->gameState = simplifier->simplifyImage(simplifyVec);
				switch (data->gameState) {
				case GameState::MarioAlive:
					data->loopCounter++;
					data->setSimpleView(*simplifyVec);
					environment->calculateStateAndActions(data->nextAction, *simplifyVec, &data->possibleActions, &data->agentStateNumber, &data->reward);
					//std::cout << "Reward: " << data->reward << std::endl;
				
					data->nextAction = agent->calculateAction(data->agentStateNumber, data->possibleActions, data->reward);
					data->agentState = agent->getState(data->agentStateNumber);
					appControl->makeAction(data->nextAction);
					break;
				case GameState::GameOver:
					numberOfCycles++;
					if (numberOfCycles % 500 == 0) {
						saveMemory();
					}
					data->marioDeathCounter++;
					data->loopCounter++;
					environment->gameOver();
					environment->calculateStateAndActions(data->nextAction, *simplifyVec, &data->possibleActions, &data->agentStateNumber, &data->reward);
					agent->calculateAction(data->agentStateNumber, data->possibleActions, data->reward);
					appControl->restartGame();
					break;
				case GameState::Win:
					numberOfCycles++;
					if (numberOfCycles % 500 == 0) {
						numberOfCycles = 0;
						saveMemory();
					}
					data->marioWinCounter++;
					data->loopCounter++;
					environment->gameWin();
					environment->calculateStateAndActions(data->nextAction, *simplifyVec, &data->possibleActions, &data->agentStateNumber, &data->reward);
					agent->calculateAction(data->agentStateNumber, data->possibleActions, data->reward);
					appControl->restartGame();
					break;
				default:
					break;
				}
			}
			
			data->featureValues = environment->getFeatureVector(data->agentStateNumber);
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
	if (environment != NULL) {
		featureValues=environment->getFeatureVector(stateNumber);
	}
	return featureValues;
}

void AiController::loadMemory(std::string path)
{
	int temp = 0;
	save.loadValues(path, environment->getStates(), agent->getStates(), &numberOfCycles, &temp);
	environment->setStatesSize(temp);
}

void AiController::saveMemory()
{
	save.saveValues(environment->getStates(), agent->getStates(), numberOfCycles, environment->getStatesSize());
}

AiController::~AiController()
{
	if (numberOfCycles > 0) {
		save.saveValues(environment->getStates(), agent->getStates(), numberOfCycles, environment->getStatesSize());
	}

	if (appControl != NULL) {
		appControl->endGame();
	}
}