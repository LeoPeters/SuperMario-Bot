#pragma once
#include <mutex>
#include <condition_variable>
#include "IAgent.h"
#include "IAppControl.h"
#include "IEnviroment.h"
#include "ISimplifier.h"
#include "IScreenCapture.h"
#include "IGuiObserver.h"
#include "AiFactory.h"
#include "AiGui.h"
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
private:
	void startSuperMario();
	AiFactory factory=AiFactory();
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	IEnviroment* enviroment;
	ISimplifier* imageScan;
	IAgent* aiAlgo;
	AiGui* gui;
	bool isPause=false;
	bool isGameStarted = false;
	std::mutex mx;
	std::condition_variable cv;
	HBITMAP gameCapture=HBITMAP();
	std::vector <std::vector<int>>* simplifyVec = new std::vector <std::vector<int>>();
	marioAction nextAction;
	int currentState;
};

