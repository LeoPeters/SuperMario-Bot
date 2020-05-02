#ifndef aigui_h
#define aigui_h
#include "ScreenCapture.h"
#include "MarioAction.h"
#include "AiData.h"
#include "MainWindow.h"

class AiGui
{
public:
	AiGui(int argc, char** argv, IGuiObserver*);
	AiData* getData();
	void runGui();
	void end();
	void update();
	MainWindow* getMainWindow();
	IGuiObserver* getObserver();
private:
	MainWindow* mWindow;
	QApplication* app;
	IGuiObserver* observer;
	QListWidget* listWidget;
	QGraphicsScene* gameView;
	QGraphicsScene* simpleView;
	QTableView* stateTableView ;
	QStandardItemModel* modelStateTableView;
	QLabel* agentStateView;
	QLabel* gameStateView;
private:
	AiData* data;
private:
	void setUpFeatureTable();
	void setUpActionView();
	void setUpTableView();

};
#endif

