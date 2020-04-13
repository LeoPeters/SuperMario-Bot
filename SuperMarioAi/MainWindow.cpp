#include <QtWin>
#include "Globals.h"
#include "MainWindow.h"
#include <iostream>
MainWindow::MainWindow(IGuiObserver* observer)
	: QMainWindow(Q_NULLPTR),
	observer(observer)
{
	ui.setupUi(this);
	connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(pressStartBtn()));
	connect(ui.btn_pause, SIGNAL(clicked()), this, SLOT(pressPauseBtn()));
	original = ui.highJumpLbl->palette();
}
MainWindow::~MainWindow()
{
	observer->notifyEndApp();
}

bool MainWindow::isActivated()
{
	return ui.centralwidget->isVisible();
}

void MainWindow::updateGameView(HBITMAP bitmap)
{
	QPixmap pixmap = QtWin::fromHBITMAP(bitmap);
	QGraphicsScene* scene=new QGraphicsScene();
	scene->addPixmap(pixmap);
	ui.viewGame->setScene(scene);
}

void MainWindow::updateSimplifyView(std::vector<std::vector<int>> simpleView)
{
	QImage image = generateSimpleImage(simpleView);
	QPixmap pixmap = QPixmap::fromImage(image);
	QGraphicsScene* scene= new QGraphicsScene();
	scene->addPixmap(pixmap.scaled((ui.viewSimplify->width() * 0.995),(ui.viewSimplify->height()*0.995)));
	ui.viewSimplify->setScene(scene);
}
void MainWindow::updateAction(action nextAction) {
	QPalette pal;
	pal.setColor(QPalette::Window, QColor(Qt::blue));
	switch (nextAction) {
	case action::highJump:
		ui.jumpLbl->setPalette(original);
		ui.shootLbl->setPalette(original);
		ui.leftLbl->setPalette(original);
		ui.rightLbl->setPalette(original);
		ui.highJumpLbl->setPalette(pal);
		break;
	case action::jump:
		ui.jumpLbl->setPalette(pal);
		ui.shootLbl->setPalette(original);
		ui.leftLbl->setPalette(original);
		ui.rightLbl->setPalette(original);
		ui.highJumpLbl->setPalette(original);
		break;
	case action::shoot:
		ui.jumpLbl->setPalette(original);
		ui.shootLbl->setPalette(pal);
		ui.leftLbl->setPalette(original);
		ui.rightLbl->setPalette(original);
		ui.highJumpLbl->setPalette(original);
		break;
	case action::moveLeft:
		ui.jumpLbl->setPalette(original);
		ui.shootLbl->setPalette(original);
		ui.leftLbl->setPalette(pal);
		ui.rightLbl->setPalette(original);
		ui.highJumpLbl->setPalette(original);
		break;
	case action::moveRight:
		ui.jumpLbl->setPalette(original);
		ui.shootLbl->setPalette(original);
		ui.leftLbl->setPalette(original);
		ui.rightLbl->setPalette(pal);
		ui.highJumpLbl->setPalette(original);
		break;
	}
}
void MainWindow::updateState(int state) {
	ui.currentState->setText(QString::number(state));
}


QImage MainWindow::generateSimpleImage(std::vector<std::vector<int>> simpleView)
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

void MainWindow::pressStartBtn()
{
	ui.btn_start->setText("Restart");
	ui.btn_pause->setText("Pause");
	observer->notifyStartPressed();
}
void MainWindow::pressPauseBtn()
{
	isPaused = !isPaused;
	if (isPaused) {
		ui.btn_pause->setText("Continue");
	}
	else {
		ui.btn_pause->setText("Pause");
	}
	Sleep(500);
	observer->notifyPausePressed();
}
bool MainWindow::getIsPaused() {
	return isPaused;
}