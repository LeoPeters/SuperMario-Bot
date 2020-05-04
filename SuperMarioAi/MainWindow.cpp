#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"
#include "MarioFeature.h"
#include "QValueTable.h"
#include "State.h"
#include "MemoryFinder.h"
#include "MainWindow.h"
MainWindow::MainWindow(IGuiObserver* observer,AiData* data)
	: QMainWindow(Q_NULLPTR),
	observer(observer),
	data(data),
	lastAgentState(0)
{
	ui.setupUi(this);
	signalSetup();
	updateMemoryList();
	//setUpFeatureTable();

}
MainWindow::~MainWindow()
{
	observer->notifyEndApp();
}


void MainWindow::signalSetup() {
	connect(ui.btn_start, SIGNAL(clicked()), this, SLOT(pressStartBtn()));
	connect(ui.btn_pause, SIGNAL(clicked()), this, SLOT(pressPauseBtn()));
	connect(ui.btn_exit, SIGNAL(clicked()), this, SLOT(pressExitBtn()));
	connect(ui.loadBtn, SIGNAL(clicked()), this, SLOT(loadMemory()));
	connect(this, SIGNAL(updateView()), this, SLOT(updateGUi()));
}

bool MainWindow::isActivated()
{
	return ui.centralwidget->isVisible();
}



void MainWindow::updateGUi()
{
	if (!data->gameView.isNull()) {
		ui.viewGame->scene()->clear();
		ui.viewGame->scene()->addPixmap(data->gameView);
	}
	if (!data->simpleView.isNull()) {
		ui.viewSimplify->scene()->clear();
		ui.viewSimplify->scene()->addPixmap(data->simpleView.scaled((ui.viewSimplify->width() * 0.995), (ui.viewSimplify->height() * 0.995)));
	}
	ui.AgentState->setText(QString::number(data->agentStateNumber));
	ui.GameState->setText(QString::fromStdString(data->gameState.toString()));

	for (int i = 0; i < data->featureValues.size();i++) {
		featureWidgetList.at(i)->setFeatureValue(data->featureValues.at(i));
	}
	updateTableView();
	updateActionView();
	ui.deathCounter->setText(QString::number(data->marioDeathCounter));
	ui.winCounter->setText(QString::number(data->marioWinCounter));
	ui.LoopTime->setText(QString::number(data->loopTime)+" ms");
	ui.loopCount->setText(QString::number(data->loopCounter));
	ui.reward->setText(QString::number(data->reward));


}


void MainWindow::updateMemoryList()
{
	MemoryFinder finder;
	std::vector<std::string> memory= finder.getAllMemoryNames();
	std::string memname;
	for (int i = 0; i < memory.size(); i++) {
		if (ui.LoadCmb->findText(QString::fromStdString(memory.at(i)))< 0) {
			ui.LoadCmb->addItem(QString::fromStdString(memory.at(i)));
		}
			
	}
}

void MainWindow::pressStartBtn()
{
	
	ui.btn_start->setText("Restart");
	ui.btn_pause->setText("Pause");
	isPaused = false;
	observer->notifyStartPressed();
}
void MainWindow::pressPauseBtn()
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
void MainWindow::pressExitBtn()
{
	observer->notifyEndApp();
}
bool MainWindow::getIsPaused() {
	return isPaused;
}

void MainWindow::setFeatureList(QListWidget* featureList, std::vector<FeatureWidget*> featureWidgetList)
{

	ui.FeatureValueLayout->addWidget( featureList);
	this->featureWidgetList = featureWidgetList;
}

void MainWindow::setActionLabelList(std::vector<QLabel*> actionLabelList)
{
	for (int i = 0; i < actionLabelList.size();i++) {
		ui.ActionLayout->addWidget(actionLabelList.at(i));
	}
	this->actionLabelList = actionLabelList;
}

void MainWindow::setgameView(QGraphicsScene* gameView)
{
	ui.viewGame->setScene(gameView);
}

void MainWindow::setSimpleView(QGraphicsScene* simpleView)
{
	ui.viewSimplify->setScene(simpleView);
}

void MainWindow::setStateTableView(QTableView* stateTable, QStandardItemModel* modelStateTableView)
{
	ui.QValueLayout->addWidget(stateTable);
	this->modelStateTableView = modelStateTableView;
}

void MainWindow::updateActionView() {
	for (int i = 0; i < actionLabelList.size(); i++) {
		actionLabelList.at(i)->hide();
		QPalette pal;
		pal.setColor(QPalette::Window, QColor(Qt::lightGray));
		actionLabelList.at(i)->setPalette(pal);
	}
	for (int i = 0; i < data->possibleActions.size(); i++) {
		int index = data->possibleActions.at(i);
		actionLabelList.at(index)->show();
		actionLabelList.at(index)->setText(QString::fromStdString(MarioAction::toString(index)+"\n")+QString::number(data->agentState.getValue(index),'g',2));
	}
	//if (data->nextAction != NULL) {
		QPalette pal;
		pal.setColor(QPalette::Window, QColor(Qt::darkGray));
		actionLabelList.at(data->nextAction)->setPalette(pal);

	//	
	//}
	//else {
	//}
}

void MainWindow::updateTableView()
{
	

	std::vector<double> row;
	for (int i = 0; i < MarioAction::size; i++) {
		row.push_back(data->lastAgentState.getValue(i));
	}
	for (int i = 0; i < data->lastFeatureValues.size(); i++) {
		row.push_back(data->lastFeatureValues.at(i));
	}
	if(lastAgentState< Max_TABLE_SIZE){
	for (int i = 0; i < row.size(); i++) {
		QModelIndex index = modelStateTableView->index(lastAgentState, i);
		modelStateTableView->setData(index, row.at(i));

	}
	}

	lastAgentState = data->agentStateNumber;
}
void MainWindow::loadWholeTableView() {
	std::vector<double> row;
	std::vector<int> features;
	for (int i = 0; i < NUMBER_OF_STATES; i++) {
		row = observer->getQValues(i);
		features = observer->getFeatureValues(i);
		for (int j = 0; j < features.size(); j++) {
			row.push_back(features.at(j));
		}
		for (int j = 0; j < row.size(); j++) {
			QModelIndex index = modelStateTableView->index(i, j);
			modelStateTableView->setData(index, row.at(j));
		}
	}
}
void MainWindow::loadMemory()
{
	MemoryFinder finder;
	std::string selectedItem = ui.LoadCmb->currentText().toStdString();
	observer->loadMemory(finder.getDirectoryPath() + selectedItem);
	loadWholeTableView();
}