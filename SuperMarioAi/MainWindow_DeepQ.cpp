#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"
#include "MarioFeature.h"
#include "State.h"
#include "MemoryFinder.h"
#include "MainWindow_DeepQ.h"
MainWindowDeepQ::MainWindowDeepQ(IGuiObserver* observer, AiData* data)
	: QMainWindow(Q_NULLPTR),
	observer(observer),
	data(data),
	lastAgentState(0)
{

	ui.setupUi(this);
	signalSetup();
	updateMemoryList();
	setUpActionView();

}
MainWindowDeepQ::~MainWindowDeepQ()
{
	observer->notifyEndApp();
}

void MainWindowDeepQ::signalSetup() {
	connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(pressStartBtn()));
	connect(ui.btn_pause, SIGNAL(clicked()), this, SLOT(pressPauseBtn()));
	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(pressExitBtn()));
	connect(ui.loadBtn, SIGNAL(clicked()), this, SLOT(loadMemory()));
	connect(this, SIGNAL(updateView()), this, SLOT(updateGUi()));
}

bool MainWindowDeepQ::isActivated()
{
	return ui.centralwidget->isVisible();
}

void MainWindowDeepQ::updateGUi()
{
	QPixmap gameView = data->getGameView();
	QPixmap simpleView = data->getSimpleView();
	if (!gameView.isNull()) {
		ui.viewGame->scene()->clear();
		ui.viewGame->scene()->addPixmap(gameView);
	}
	if (!simpleView.isNull()) {
		ui.viewSimplify->scene()->clear();
		ui.viewSimplify->scene()->addPixmap(simpleView.scaled((ui.viewSimplify->width() * 0.995), (ui.viewSimplify->height() * 0.995)));
	}
	ui.GameState->setText(QString::fromStdString(data->gameState.toString()));
	updateActionView();
	ui.deathCounter->setText(QString::number(data->marioDeathCounter));
	ui.winCounter->setText(QString::number(data->marioWinCounter));
	ui.LoopTime->setText(QString::number(data->loopTime) + " ms");
	ui.loopCount->setText(QString::number(data->loopCounter));
	ui.reward->setText(QString::number(data->reward));
}

void MainWindowDeepQ::updateMemoryList()
{
	MemoryFinder finder;
	std::vector<std::string> memory = finder.getAllMemoryNames();
	std::string memname;
	for (int i = 0; i < memory.size(); i++) {
		if (ui.LoadCmb->findText(QString::fromStdString(memory.at(i))) < 0) {
			ui.LoadCmb->addItem(QString::fromStdString(memory.at(i)));
		}
	}
}

void MainWindowDeepQ::pressStartBtn()
{
	ui.btn_start->setText("Restart");
	ui.btn_pause->setText("Pause");
	isPaused = false;
	observer->notifyStartPressed();
}
void MainWindowDeepQ::pressPauseBtn()
{
	if (timer.elapsed() > 1000) {
		timer.restart();
		isPaused = !isPaused;
		if (isPaused) {
			ui.btn_pause->setText("Continue");
		}
		else {
			ui.btn_pause->setText("Pause");
		}

		observer->notifyPausePressed();
	}
}
void MainWindowDeepQ::pressExitBtn()
{
	observer->notifyEndApp();
}
bool MainWindowDeepQ::getIsPaused() {
	return isPaused;
}

void MainWindowDeepQ::setActionLabelList(std::vector<QLabel*> actionLabelList)
{
	for (int i = 0; i < actionLabelList.size(); i++) {
		ui.ActionLayout->addWidget(actionLabelList.at(i));
	}
}

void MainWindowDeepQ::setgameView(QGraphicsScene* gameView)
{
	ui.viewGame->setScene(gameView);
}

void MainWindowDeepQ::setSimpleView(QGraphicsScene* simpleView)
{
	ui.viewSimplify->setScene(simpleView);
}



void MainWindowDeepQ::updateActionView(){
	for (int i = 0; i < actionLabelList.size(); i++) {
		QPalette pal;
		pal.setColor(QPalette::Window, QColor(Qt::lightGray));
		actionLabelList.at(i)->setPalette(pal);
	}
	for (int i = 0; i < data->possibleActions.size(); i++) {
		int index = data->possibleActions.at(i);
		actionLabelList.at(index)->setText(QString::fromStdString(MarioAction::toString(index) + "\n") + QString::number(data->agentState.getValue(index), 'g', 2));
	}
	QPalette pal;
	pal.setColor(QPalette::Window, QColor(Qt::darkGray));
	actionLabelList.at(data->nextAction)->setPalette(pal);
}




void MainWindowDeepQ::loadMemory()
{
	MemoryFinder finder;
	std::string selectedItem = ui.LoadCmb->currentText().toStdString();
	observer->loadMemory(finder.getDirectoryPath() + selectedItem);
}


void MainWindowDeepQ::setUpActionView() {
	for (int i = 0; i < MarioAction::size; i++) {
		QPalette pal;
		pal.setColor(QPalette::Window, QColor(Qt::lightGray));
		QLabel* newAction = new QLabel();
		newAction->setText(QString::fromStdString(MarioAction::toString(i)));
		newAction->setPalette(pal);
		newAction->setAutoFillBackground(true);
		newAction->setLayoutDirection(Qt::LeftToRight);
		newAction->setAlignment(Qt::AlignCenter);
		actionLabelList.push_back(newAction);
	}
	setActionLabelList(actionLabelList);
}
