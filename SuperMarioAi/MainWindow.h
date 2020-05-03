#ifndef mainwindow_h
#define mainwindow_h
#include <QMainWindow>
#include "QValueTable.h"
#include "IGuiObserver.h"
#include "MarioAction.h"
#include <QStandardItemModel>
#include "AiData.h"
#include "FeatureWidget.h"
#include "MarioFeature.h"
#include "GameState.h"
#include "ui_MainWindow.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(IGuiObserver*, AiData * data);
	~MainWindow();
	bool isActivated();
	bool getIsPaused();
	void setFeatureList(QListWidget* featureList, std::vector<FeatureWidget*> featureWidgetList);
	void setActionLabelList(std::vector<QLabel*> actionLabelList);
	void setgameView(QGraphicsScene* gameView);
	void setSimpleView(QGraphicsScene* simpleView);
	void setStateTableView(QTableView* stateTable, QStandardItemModel* modelStateTableView);
	void updateActionView();
	void updateTableView();
signals:
	void updateView();

private:
	AiData* data;
	QElapsedTimer timer;
	Ui::MainWindow ui;
	IGuiObserver* observer;
	bool isPaused = false;
	QStandardItemModel* modelStateTableView;
	std::vector<QLabel*> actionLabelList;
	std::vector<FeatureWidget*> featureWidgetList;
	int lastAgentState;
	
private:
	void signalSetup();
	void updateMemoryList();
	void loadWholeTableView();

private slots:
	void pressStartBtn();
	void pressPauseBtn();
	void pressExitBtn();
	void updateGUi();
	void loadMemory();

	
};
#endif
