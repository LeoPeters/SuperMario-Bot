#include "AiGui.h"

AiGui::AiGui(int argc, char** argv, IGuiObserver* observer){
	app = new QApplication(argc, argv);
	mWindow = new MainWindow(observer);
	mWindow->show();
}

void AiGui::update(HBITMAP gameView, std::vector<std::vector<int>> simpleView, marioAction nextaction,int state)
{
	if (gameView != NULL) {
	mWindow->updateGameView(gameView);
	}
	if ((simpleView.size()>0)) {
		mWindow->updateSimplifyView(simpleView);
	}
	mWindow->updateAction(nextaction);
	mWindow->updateState(state);
	app->processEvents();
}

bool AiGui::mainWindowIsVisible()
{
	return mWindow->isActivated();
}

bool AiGui::isPaused() {
	return mWindow->getIsPaused();
}
MainWindow* AiGui::getMainWindow()
{
	return mWindow;
}
