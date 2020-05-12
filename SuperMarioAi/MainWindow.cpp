#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"
#include "MarioFeature.h"
#include "State.h"
#include "MemoryFinder.h"
#include "MainWindow.h"
MainWindow::MainWindow(IGuiObserver* observer, AiData* data)
	: QMainWindow(Q_NULLPTR),
	observer(observer),
	data(data),
	lastAgentState(0)
{
	stateTableView = new QTableView();
	listWidget = new QListWidget();
	ui.setupUi(this);
	signalSetup();
	updateMemoryList();
	ui.QValueLayout->addWidget(stateTableView);
	ui.FeatureValueLayout->addWidget(listWidget);
	//setUpFeatureTable();
	setUp();
	setUpActionView();
	stateTableView->resizeColumnsToContents();
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
	ui.AgentState->setText(QString::number(data->agentStateNumber));
	ui.GameState->setText(QString::fromStdString(data->gameState.toString()));

	for (int i = 0; i < featureWidgetList.size(); i++) {
		if (i< data->featureValues.size()) {
		featureWidgetList.at(i)->setFeatureValue(data->featureValues.at(i));
		}
	}
	updateTableView();
	updateActionView();
	ui.deathCounter->setText(QString::number(data->marioDeathCounter));
	ui.winCounter->setText(QString::number(data->marioWinCounter));
	ui.LoopTime->setText(QString::number(data->loopTime) + " ms");
	ui.loopCount->setText(QString::number(data->loopCounter));
	ui.reward->setText(QString::number(data->reward));
	lastAgentState = data->agentStateNumber;
}

void MainWindow::updateMemoryList()
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
	ui.FeatureValueLayout->addWidget(featureList);
}

void MainWindow::setActionLabelList(std::vector<QLabel*> actionLabelList)
{
	for (int i = 0; i < actionLabelList.size(); i++) {
		ui.ActionLayout->addWidget(actionLabelList.at(i));
	}
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
		actionLabelList.at(index)->setText(QString::fromStdString(MarioAction::toString(index) + "\n") + QString::number(data->agentState.getValue(index), 'g', 2));
	}
	QPalette pal;
	pal.setColor(QPalette::Window, QColor(Qt::darkGray));
	actionLabelList.at(data->nextAction)->setPalette(pal);
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
	if (lastAgentState < Max_TABLE_SIZE) {
		for (int i = 0; i < row.size(); i++) {
			QModelIndex index = modelStateTableView->index(lastAgentState, i);
			modelStateTableView->setData(index, row.at(i));
		}
	}
}
void MainWindow::setUp()
{
	setUpTableView();
	setUpFeatureTable();
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
	setUp();
	loadWholeTableView();
}

void MainWindow::setUpFeatureTable()
{
	ui.FeatureValueLayout->removeWidget(listWidget);
	for (int i = 0; i < featureWidgetList.size(); i++) {
		delete featureWidgetList.at(i) ;
	}
	featureWidgetList.clear();
	listWidget=new QListWidget();
	for (int i = 0; i < data->activeFeatures.size(); i++) {
		FeatureWidget* wg = new FeatureWidget();
		QListWidgetItem* listitem = new QListWidgetItem();
		listitem->setBackgroundColor(Qt::GlobalColor::lightGray);
		listitem->setSizeHint(wg->sizeHint());
		wg->setFeatureName(data->activeFeatures.at(i).toString() + ": ");
		listWidget->addItem(listitem);
		listWidget->setItemWidget(listitem, wg);
		featureWidgetList.push_back(wg);
	}
	ui.FeatureValueLayout->addWidget(listWidget);

}

void MainWindow::setUpActionView() {
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
void MainWindow::setUpTableView()
{
	QStringList headerList;
	if (NUMBER_OF_STATES < Max_TABLE_SIZE / (MarioAction::size + data->activeFeatures.size())) {
		modelStateTableView = new QStandardItemModel(NUMBER_OF_STATES, MarioAction::size + data->activeFeatures.size());
	}
	else {
		modelStateTableView = new QStandardItemModel(Max_TABLE_SIZE / (MarioAction::size + data->activeFeatures.size()), MarioAction::size + data->activeFeatures.size());
	}
	for (int i = 0; i < MarioAction::size; i++) {
		headerList.append("Q-Value: " + QString::fromStdString(MarioAction::toString(i)));
	}
	for (int i = 0; i < data->activeFeatures.size(); i++) {
		headerList.append("Feature: " + QString::fromStdString(data->activeFeatures.at(i).toString()));
	}
	modelStateTableView->setHorizontalHeaderLabels(headerList);
	stateTableView->setModel(modelStateTableView);
}