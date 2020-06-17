#include "AiGuiDQN.h"
#include <QtWin>
#include "Globals.h"
#include <iostream>

AiGuiDQN::AiGuiDQN(int argc, char** argv, IGuiObserver* observer, AiData* data) :
	observer(observer),
	data(data)
{
	app = new QApplication(argc, argv);
	mWindow = new MainWindowDeepQ(observer, data);
	mWindow->show();

	gameView = new QGraphicsScene();
	simpleView = new QGraphicsScene();
	mWindow->setSimpleView(simpleView);
	mWindow->setgameView(gameView);
}
void AiGuiDQN::setData(AiData* newData) {
	data = newData;
}
void AiGuiDQN::runGui()
{
	app->exec();
}

void AiGuiDQN::end()
{
	app->quit();
}

void AiGuiDQN::update()
{
	mWindow->updateView();
}

MainWindowDeepQ* AiGuiDQN::getMainWindow()
{
	return mWindow;
}

IGuiObserver* AiGuiDQN::getObserver()
{
	return observer;
}
