#ifndef aicontroller_h
#define aicontroller_h
#include <mutex>
#include <condition_variable>
#include "IAgent.h"
#include "IAppControl.h"
#include "IEnvironment.h"
#include "ISimplifier.h"
#include "IScreenCapture.h"
#include "IGuiObserver.h"
#include "AiFactory.h"
#include "GameState.h"
#include "AiGui.h"
#include "AiData.h"
#include "Save.h"

class AiController:public IGuiObserver
{
public:
	AiController(int argc, char** argv);
	~AiController();
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
	void startSuperMario();
	std::vector<MarioAction> possibleActions;
	double reward;
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	IEnvironment* environment;
	ISimplifier* simplifier;
	IAgent* agent;
	AiGui* gui;
	bool isPause=false;
	bool isGameStarted = false;
	bool isGuiRunning = true;
	AiFactory factory=AiFactory();
	std::vector <std::vector<int>>* simplifyVec = new std::vector <std::vector<int>>();
	HBITMAP gameCapture=HBITMAP();
	State agentStateArray;
	AiData* data;
	Save save;
	int numberOfCycles;
};

#endif