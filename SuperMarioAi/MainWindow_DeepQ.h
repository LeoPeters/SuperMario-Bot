#ifndef mainwindow_deepQ_h
#define mainwindow_deepQ_h
#include <QMainWindow>
#include "IGuiObserver.h"
#include "MarioAction.h"
#include <QStandardItemModel>
#include "AiData.h"
#include "FeatureWidget.h"
#include "MarioFeature.h"
#include "GameState.h"
#include "ui_MainWindow_DeepQ.h"
class MainWindowDeepQ : public QMainWindow
{
	Q_OBJECT

public:

	MainWindowDeepQ(IGuiObserver*, AiData * data);
	~MainWindowDeepQ();
	bool isActivated();
	bool getIsPaused();
	void setActionLabelList(std::vector<QLabel*> actionLabelList);
	void setgameView(QGraphicsScene* gameView);
	void setSimpleView(QGraphicsScene* simpleView);
	void updateActionView();

signals:
	void updateView();

private:
	AiData* data;
	QElapsedTimer timer;
	Ui::MainWindowDeepQ ui;
	IGuiObserver* observer;
	bool isPaused = false;
	QStandardItemModel* modelStateTableView;
	std::vector<QLabel*> actionLabelList;
	std::vector<FeatureWidget*> featureWidgetList;
	int lastAgentState;
	QTableView* stateTableView;
	QListWidget* listWidget;
private:
	void signalSetup();
	void updateMemoryList();
	void setUpActionView();


private slots:
	void pressStartBtn();
	void pressPauseBtn();
	void pressExitBtn();
	void updateGUi();
	void loadMemory();

	

	
};
#endif
