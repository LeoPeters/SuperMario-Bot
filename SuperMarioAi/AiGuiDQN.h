#pragma once
#include "ScreenCapture.h"
#include "MarioAction.h"
#include "AiData.h"
#include "MainWindow.h"
#include "MainWindow_DeepQ.h"
#include "MarioFeature.h"

class AiGuiDQN
{
public:
	AiGuiDQN(int argc, char** argv, IGuiObserver*, AiData* data);
	void setData(AiData* newData);

	void runGui();
	void end();
	void update();
	MainWindowDeepQ* getMainWindow();
	IGuiObserver* getObserver();
private:
	MainWindowDeepQ* mWindow;
	QApplication* app;
	IGuiObserver* observer;
	QGraphicsScene* gameView;
	QGraphicsScene* simpleView;
	QLabel* agentStateView;
	QLabel* gameStateView;
private:
	AiData* data;

};

