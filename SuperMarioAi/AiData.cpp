#include "Aidata.h"
#include <QtWin>

QPixmap AiData::generateSimpleView(std::vector<std::vector<int>> simpleView)
{
	QPixmap pixmap;
	QImage image(1, 1, QImage::Format_RGB32);
	image.setPixel(0, 0, black);
	if (simpleView.size() > 0) {
		image = QImage(simpleView[0].size(), simpleView.size(), QImage::Format_RGB32);
		for (int y = 0; y < simpleView.size(); y++) {
			for (int x = 0; x < simpleView[y].size(); x++) {
				switch (simpleView[y][x]) {
				case emptyValue:
					image.setPixel(x, y, skyBlue);
					break;
				case marioValue:
					image.setPixel(x, y, red);
					break;
				case groundValue:
					image.setPixel(x, y, brown);
					break;
				case enemyValue:
					image.setPixel(x, y, black);
					break;
				case itemValue:
					image.setPixel(x, y, yellow);
					break;
				case finishFlagValue:
					image.setPixel(x, y, darkGreen);
					break;
				default:
					image.setPixel(x, y, brown);
					break;
				}
			}
		}
	}
	pixmap = QPixmap::fromImage(image);
	return pixmap;
}

QPixmap AiData::getSimpleView()
{
	return generateSimpleView(simpleView);
}

QPixmap AiData::getGameView()
{
	return QtWin::fromHBITMAP(gameView);
}

void AiData::reset() {
	actionList.clear();
	featureValues.clear();
	possibleActions.clear();
	agentStateNumber = 0;
	marioDeathCounter = 0;
	marioWinCounter = 0;
}