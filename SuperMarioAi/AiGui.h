#pragma once
#include "ScreenCapture.h"
#include "MainWindow.h"
#include "MarioAction.h"
class AiGui
{
public:
	AiGui(int argc, char** argv, IGuiObserver*);
	void update(HBITMAP gameView, std::vector<std::vector<int>> simpleView, marioAction nextaction, int state);
	bool mainWindowIsVisible();
	MainWindow* getMainWindow();
	bool isPaused();
private:
	MainWindow* mWindow;
	QApplication* app;
};

