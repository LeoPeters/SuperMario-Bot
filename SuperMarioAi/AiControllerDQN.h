#pragma once
#include <mutex>
#include <condition_variable>
#include "AgentDQN.h"
#include "IAppControl.h"
#include "IEnvironment.h"
#include "ISimplifier.h"
#include "IScreenCapture.h"
#include "IGuiObserver.h"
#include "AiFactory.h"
#include "GameState.h"
#include "AiGuiDQN.h"
#include "AiData.h"
#include "Memory.h"
#include "EnvironmentDQN.h"

class AiControllerDQN:public IGuiObserver
{
public:
	AiControllerDQN(int argc, char** argv);
	~AiControllerDQN();
	void run();
	void runGui();
	void notifyPausePressed() override;
	void notifyStartPressed() override;
	void notifyEndApp() override;
	std::vector<double> getQValues(int stateNumber) override;
	std::vector<int> getFeatureValues(int stateNumber) override;
	void loadMemory(std::string path) override;
	virtual void saveMemory() override;

private:

	double reward;
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	ISimplifier* simplifier;
	EnvironmentDQN env;
	AgentDQN agent;
	AiGuiDQN* gui;
	bool isPause = false;
	bool isGameStarted = false;
	bool isGuiRunning = true;
	State agentStateArray;
	AiData* data;
	Memory memory;
	int numberOfCycles;
	void startSuperMario();
	AiFactory factory = AiFactory();
	std::vector <std::vector<int>>* simplifyVec = new std::vector <std::vector<int>>();
	HBITMAP gameCapture = HBITMAP();
	std::vector<unsigned char> newStateData;
};

