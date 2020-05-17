#include <vector>
#include <iostream>
#include "MarioWindow.h"
#include "Globals.h"
#include "AiController.h"
#include "EnvironmentCalculation.h"
#include "Agent.h"
#include "AgentDummy.h"

AiController::AiController(int argc, char** argv) :
	screenCapture(NULL),
	simplifier(NULL),
	environment(NULL),
	agent(NULL),
	appControl(NULL),
	numberOfCycles(0)
{

	data = new AiData();
	data->activeFeatures.push_back(MarioFeature::closestEnemyX);
	data->activeFeatures.push_back(MarioFeature::closestEnemyY);
	data->activeFeatures.push_back(MarioFeature::distanceToHole);
	//data->activeFeatures.push_back(MarioFeature::isEnemyLeft);
	//data->activeFeatures.push_back(MarioFeature::isRightFromObstacle);
	data->activeFeatures.push_back(MarioFeature::numberOfEnemies);
	data->activeFeatures.push_back(MarioFeature::obstacleHeight);
	data->activeFeatures.push_back(MarioFeature::distanceToObstacle);
	agent = new Agent();
	environment = new EnvironmentCalculation();
	gui = new AiGui(argc, argv, this,data);
	environment->setActiveFeatures(data->activeFeatures);
}

void AiController::run() {
	while (isGuiRunning) {
		while (isGameStarted) {
			data->gameView=screenCapture->captureScreen(PNG_LNAME);
			if (!gui->getMainWindow()->getIsPaused()) {
			auto start = std::chrono::high_resolution_clock::now();
				data->lastAgentState = data->agentState;
				data->lastFeatureValues = data->featureValues;
				data->gameState = simplifier->simplifyImage(simplifyVec);
				auto stop = std::chrono::high_resolution_clock::now();
				switch (data->gameState) {
				case GameState::MarioAlive:
					data->loopCounter++;
					data->simpleView=*simplifyVec;
					environment->calculateStateAndActions(data->nextAction, *simplifyVec, &data->possibleActions, &data->agentStateNumber, &data->reward);
					//std::cout << "Reward: " << data->reward << std::endl;
					data->nextAction = agent->calculateAction(data->agentStateNumber, data->possibleActions, data->reward);
					
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
					data->agentState = agent->getState(data->agentStateNumber);
					
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
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			auto fps = duration.count();
			data->loopTime = (int)fps;
			}

			
			data->agentState = agent->getState(data->agentStateNumber);
			data->featureValues = environment->getFeatureVector(data->agentStateNumber);
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
	SaveLoad *saveLoad = new SaveLoad();
	data->activeFeatures.clear();

	memory.loadValues(path, saveLoad);

	numberOfCycles = saveLoad->numberOfCycles;
	environment->setStatesSize(saveLoad->statesSize);
	data->marioWinCounter = saveLoad->numberOfWins;
	data->marioDeathCounter = saveLoad->numberOfDeaths;
	data->activeFeatures = saveLoad->activeFeatures;
	*environment->getStates() = saveLoad->featureValues;
	*agent->getStates() = saveLoad->scores;
	environment->setActiveFeatures(saveLoad->activeFeatures);
	delete saveLoad;
}

void AiController::saveMemory()
{
	SaveLoad *saveLoad = new SaveLoad();
	saveLoad->numberOfCycles = numberOfCycles;
	saveLoad->statesSize = environment->getStatesSize();
	saveLoad->numberOfWins = data->marioWinCounter;
	saveLoad->numberOfDeaths = data->marioDeathCounter;
	saveLoad->activeFeatures = data->activeFeatures;
	saveLoad->featureValues = *environment->getStates();
	saveLoad->scores = *agent->getStates();

	memory.saveValues(saveLoad);
	delete saveLoad;
}

AiController::~AiController()
{
	if (numberOfCycles > 0) {
		saveMemory();
	}

	if (appControl != NULL) {
		appControl->endGame();
	}
}