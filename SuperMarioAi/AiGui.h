#pragma once
#include "ScreenCapture.h"
#include "MainWindow.h"
#include "ActionEnum.h"
class AiGui
{
public:
	AiGui(int argc, char** argv, IGuiObserver*);
	void update(HBITMAP gameView, std::vector<std::vector<int>> simpleView, Action nextaction, int state);
	bool mainWindowIsVisible();
	MainWindow* getMainWindow();
	bool isPaused();
private:
	MainWindow* mWindow;
	QApplication* app;
};

