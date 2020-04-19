#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"
#include "FeatureNames.h"
#include "MainWindow.h"

MainWindow::MainWindow(IGuiObserver* observer)
	: QMainWindow(Q_NULLPTR),
	observer(observer),
	gameScene(new QGraphicsScene()),
	simpleScene(new QGraphicsScene())
{
	ui.setupUi(this);
	signalSetup();
	original = ui.highJumpLbl->palette();
	ui.viewGame->setScene(gameScene);
	ui.viewSimplify->setScene(simpleScene);
	setUpFeatureGrid();
	
}
MainWindow::~MainWindow()
{
	observer->notifyEndApp();
}

void MainWindow::setUpFeatureGrid()
{
	ui.gridLayout->setSpacing(1);
	FeatureWidget* currentState=new FeatureWidget();
	featureWidgets.push_back(currentState);
	ui.gridLayout->addWidget(currentState);
	for (int i = 0; i < (int)FeatureNames::SIZE_FEATURE_NAMES; i++) {
		FeatureWidget* wg = new FeatureWidget();
		featureWidgets.push_back(wg);
		ui.gridLayout->addWidget(wg);
	}
	featureWidgets[0]->setFeatureName("Current State:");
	featureWidgets[1]->setFeatureName("Under Block: ");
	featureWidgets[2]->setFeatureName("Enemy X:");
	featureWidgets[3]->setFeatureName("Enemy Y:");
	featureWidgets[4]->setFeatureName("Obstacle:");

}
void MainWindow::signalSetup() {
	connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(pressStartBtn()));
	connect(ui.btn_pause, SIGNAL(clicked()), this, SLOT(pressPauseBtn()));
	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(pressExitBtn()));
	connect(this, SIGNAL(updateView()), this, SLOT(updateGUi()));
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
	featureWidgets[0]->setFeatureValue(state);
	for (int i = 0; i < featureVector.size(); i++) {
		featureWidgets[i+1]->setFeatureValue(featureVector[i]);
	}

	
}


void MainWindow::setAction(MarioAction nextAction) {
	action = nextAction;
}
void MainWindow::setFeatureVector(std::vector<int> featureVector)
{
	this->featureVector = featureVector;
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
