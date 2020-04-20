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
	 int getState() override;
	 std::vector <std::vector<int>> getSimpleView() override;
	 HBITMAP getGameView() override;
	 MarioAction getAction() override;
	 std::vector<MarioAction> getpossibleAction() override;
	 std::vector<int> getFeatureVector();
	 GameState getGameState() override;
private:

	std::vector<MarioAction> possibleActions;
	void startSuperMario();
	AiFactory factory=AiFactory();
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	IEnvironment* features;
	ISimplifier* simplifier;
	IAgent* agent;
	AiGui* gui;
	bool isPause=false;
	bool isGameStarted = false;
	bool isGuiRunning = true;
	std::mutex mx;
	std::condition_variable cv;
	HBITMAP gameCapture=HBITMAP();
	std::vector <std::vector<int>>* simplifyVec = new std::vector <std::vector<int>>();
	MarioAction nextAction;
	int currentState;
	std::vector<int> featureVector;
	GameState gameState;
};

#endif