#include <QtWin>
#include "Globals.h"
#include <iostream>
#include "AiGui.h"
AiGui::AiGui(int argc, char** argv, IGuiObserver* observer, std::vector < MarioFeature> activeFeatures) :
	observer(observer),
	activeMarioFeatures(activeFeatures)
{
	app = new QApplication(argc, argv);
	data = new AiData();
	mWindow = new MainWindow(observer,data);
	mWindow->show();
	setUpTableView();
	setUpFeatureTable();
	setUpActionView();
	gameView = new QGraphicsScene();
	simpleView = new QGraphicsScene();
	mWindow->setSimpleView(simpleView);
	mWindow->setgameView(gameView);
	
}
AiData* AiGui::getData() {
	return data;
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





void AiGui::setUpFeatureTable()
{
	std::vector<FeatureWidget*> featureWidgetList;
	listWidget = new QListWidget();
	for (int i = 0; i < activeMarioFeatures.size(); i++) {
		FeatureWidget* wg = new FeatureWidget();
		QListWidgetItem* listitem = new QListWidgetItem();
		listitem->setBackgroundColor(Qt::GlobalColor::lightGray);
		listitem->setSizeHint(wg->sizeHint());
		wg->setFeatureName(activeMarioFeatures.at(i).toString() + ": ");
		listWidget->addItem(listitem);
		listWidget->setItemWidget(listitem, wg);
		featureWidgetList.push_back(wg);
	}
	mWindow->setFeatureList(listWidget, featureWidgetList);
}

void AiGui::setUpActionView() {
	std::vector<QLabel*> actionLabelList;
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
	mWindow->setActionLabelList(actionLabelList);
}
void AiGui::setUpTableView()
{
	stateTableView = new QTableView();
	QStringList headerList;
	if (NUMBER_OF_STATES< Max_TABLE_SIZE/( MarioAction::size + activeMarioFeatures.size())) {

		modelStateTableView = new QStandardItemModel(NUMBER_OF_STATES, MarioAction::size + activeMarioFeatures.size());
	}
	else {
		modelStateTableView = new QStandardItemModel(Max_TABLE_SIZE / (MarioAction::size + activeMarioFeatures.size()), MarioAction::size + activeMarioFeatures.size());
	}
	for (int i = 0; i < MarioAction::size; i++) {
		headerList.append("Q-Value: " + QString::fromStdString(MarioAction::toString(i)));
	}
	for (int i = 0; i < activeMarioFeatures.size(); i++) {
		headerList.append("Feature: " + QString::fromStdString(activeMarioFeatures.at(i).toString()));
	}
	modelStateTableView->setHorizontalHeaderLabels(headerList);
	stateTableView->setModel(modelStateTableView);
	stateTableView->resizeColumnsToContents();
	mWindow->setStateTableView(stateTableView, modelStateTableView);
}
