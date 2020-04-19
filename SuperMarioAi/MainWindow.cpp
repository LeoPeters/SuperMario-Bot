#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"


#include "MainWindow.h"
MainWindow::MainWindow(IGuiObserver* observer)
	: QMainWindow(Q_NULLPTR),
	observer(observer)
{

	ui.setupUi(this);
	connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(pressStartBtn()));
	connect(ui.btn_pause, SIGNAL(clicked()), this, SLOT(pressPauseBtn()));
	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(pressExitBtn()));
	connect(this, SIGNAL(updateView()), this, SLOT(updateGUi()));
	original = ui.highJumpLbl->palette();
	gameScene = new QGraphicsScene();
	simpleScene = new QGraphicsScene();
	ui.viewGame->setScene(gameScene);
	ui.viewSimplify->setScene(simpleScene);

	ui.tableWidget->setColumnCount(2);
	ui.tableWidget->setColumnWidth(0,(ui.tableWidget->geometry().width() * 0.499));
	ui.tableWidget->setColumnWidth(1, (ui.tableWidget->geometry().width() *0.499));
	ui.tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Feature-Name"));
	ui.tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));

}
MainWindow::~MainWindow()
{
	observer->notifyEndApp();
}

bool MainWindow::isActivated()
{
	return ui.centralwidget->isVisible();
}

void MainWindow::setUpTable() {

}

void MainWindow::updateGUi()
{
	if (!simplePixmap.isNull()) {
		QPixmap scale;
		scale =(simplePixmap.scaled((ui.viewSimplify->width() * 0.995), (ui.viewSimplify->height() * 0.995)));
		simpleScene->clear();
		simpleScene->addPixmap(scale);
	}
	if (!gamePixmap.isNull()) {
		gameScene->clear();
		gameScene->addPixmap(gamePixmap);
	}
	setActionLabel();
	ui.currentState->setText(QString::number(state));
}


void MainWindow::setAction(MarioAction nextAction) {
	action = nextAction;
}
void MainWindow::setPossibleAction(std::vector<MarioAction> possibleActions) {
	this->possibleActions = possibleActions;
}

void MainWindow::setActionLabelPalette( QPalette left,QPalette jump,QPalette highJump, QPalette shootl, QPalette right)
{
	ui.jumpLbl->setPalette(jump);
	ui.shootLbl->setPalette(shootl);
	ui.leftLbl->setPalette(left);
	ui.rightLbl->setPalette(right);
	ui.highJumpLbl->setPalette(highJump);
}

void MainWindow::setPossibleActionLabel() {
	ui.highJumpLbl->hide();
	ui.jumpLbl->hide();
	ui.shootLbl->hide();
	ui.leftLbl->hide();
	ui.rightLbl->hide();
	for (int i = 0; i < possibleActions.size(); i++) {
		if (possibleActions[i] == MarioAction::highJump) ui.highJumpLbl->show() ;
		if (possibleActions[i] == MarioAction::jump) ui.jumpLbl->show();
		if (possibleActions[i] == MarioAction::moveLeft) ui.leftLbl->show();
		if (possibleActions[i] == MarioAction::moveRight) ui.rightLbl->show();
		if (possibleActions[i] == MarioAction::shoot) ui.shootLbl->show();
	}
}

void MainWindow::setActionLabel()
{
	setPossibleActionLabel();
	QPalette pal;
	pal.setColor(QPalette::Window, QColor(Qt::blue));
	switch (action) {
	case MarioAction::highJump:

		setActionLabelPalette(original, original, pal, original, original);
		break;
	case MarioAction::jump:
		setActionLabelPalette(original, pal, original, original, original);
		break;
	case MarioAction::shoot:

		setActionLabelPalette(original, original, original, pal, original);
		break;
	case MarioAction::moveLeft:
		setActionLabelPalette(pal, original, original, original, original);
		break;
	case MarioAction::moveRight:
		setActionLabelPalette(original, original, original, original, pal);
		break;
	}
}

void MainWindow::setState(int state) {
	this->state = state;
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
void MainWindow::pressExitBtn()
{
	observer->notifyEndApp();
}
bool MainWindow::getIsPaused() {
	return isPaused;
}

void MainWindow::setGamePixmap(QPixmap pixmap)
{
	gamePixmap = pixmap;
}

void MainWindow::setSimplePixmap(QPixmap pixmap)
{
	simplePixmap = pixmap;
}
