#ifndef aigui_h
#define aigui_h
#include "ScreenCapture.h"
#include "MarioAction.h"
#include "AiData.h"
#include "MainWindow.h"
#include "MarioFeature.h"

class AiGui
{
public:
	AiGui(int argc, char** argv, IGuiObserver*, AiData* data);
	void setData(AiData* newData);

	void runGui();
	void end();
	void update();
	MainWindow* getMainWindow();
	IGuiObserver* getObserver();
private:
	MainWindow* mWindow;
	QApplication* app;
	IGuiObserver* observer;
	QGraphicsScene* gameView;
	QGraphicsScene* simpleView;
	QLabel* agentStateView;
	QLabel* gameStateView;
private:
	AiData* data;


};
#endif

