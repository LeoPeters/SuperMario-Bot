#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"
AiGui::AiGui(int argc, char** argv, IGuiObserver* observer):
	observer(observer)
{
	app = new QApplication(argc, argv);

	mWindow = new MainWindow(observer);
	mWindow->show();
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
	if (observer->getGameView() != NULL) {
		QPixmap pixmap = QtWin::fromHBITMAP(*observer->getGameView());
		mWindow->setGamePixmap(pixmap);
		
		
	}
	if ((observer->getSimpleView()->size()>0)) {
		QImage simView = generateSimpleImage(*observer->getSimpleView());
		QPixmap pixmap = QPixmap::fromImage(simView);
		mWindow->setSimplePixmap(pixmap);
	}
	mWindow->setState(*observer->getState());
	mWindow->setAction(*observer->getAction());
	mWindow->updateView();
}

MainWindow* AiGui::getMainWindow()
{
	return mWindow;
}

IGuiObserver* AiGui::getObserver()
{
	return observer;
}

QImage AiGui::generateSimpleImage(std::vector<std::vector<int>> simpleView)
{
	QImage image(simpleView[0].size(), simpleView.size(), QImage::Format_RGB32);
	for (int y = 0; y < simpleView.size(); y++) {
		for (int x = 0; x < simpleView[y].size(); x++) {
			switch (simpleView[y][x]) {
			case SKY:
				image.setPixel(x, y, skyColor);
				break;
			case MARIO:
				image.setPixel(x, y, marioColor);
				break;
			case BLOCK:
				image.setPixel(x, y, blockColor);
				break;
			case ENEMY:
				image.setPixel(x, y, enemyColor);
				break;
			case ITEM:
				image.setPixel(x, y, itemColor);
				break;
			default:
				image.setPixel(x, y, blockColor);
				break;
			}
		}
	}
	return image;
}