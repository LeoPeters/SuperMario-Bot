#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"
AiGui::AiGui(int argc, char** argv, IGuiObserver* observer,AiData* data) :
	observer(observer),
	data(data)
{
	app = new QApplication(argc, argv);
	mWindow = new MainWindowDeepQ(observer,data);
	mWindow->show();
	
	gameView = new QGraphicsScene();
	simpleView = new QGraphicsScene();
	mWindow->setSimpleView(simpleView);
	mWindow->setgameView(gameView);	
}
void AiGui::setData(AiData* newData) {
	data = newData;
}
void AiGui::runGui()
{
	app->exec();
}

void AiGui::end()
{
	app->quit();
}

void AiGui::update()
{
	mWindow->updateView();
}

MainWindowDeepQ* AiGui::getMainWindow()
{
	return mWindow;
}

IGuiObserver* AiGui::getObserver()
{
	return observer;
}





