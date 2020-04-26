#ifndef mainwindow_h
#define mainwindow_h
#include <QMainWindow>
#include "QValueTable.h"
#include "IGuiObserver.h"
#include "MarioAction.h"
#include <QStandardItemModel>
#include "FeatureWidget.h"
#include "FeatureNames.h"
#include "GameState.h"
#include "ui_MainWindow.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(IGuiObserver*);
	~MainWindow();
	
	bool isActivated();
	
	void setAction(MarioAction nextAction);
	void setFeatureVector(std::vector<int> featureVector);
	void setPossibleAction(std::vector<MarioAction> nextAction);
	void setState(int);
	void updateStateTable();
	bool getIsPaused();
	void setGamePixmap(QPixmap);
	void setSimplePixmap(QPixmap);
	void setGameState(GameState);
	void setAgentStateArray(std::array<State, NUMBER_OF_STATES> agentStateArray);
signals:
	void updateView();

private:
	QValueTable* qValueTable;
	void signalSetup();
	void setActionLabelPalette(QPalette jump, QPalette left, QPalette right, QPalette highJump, QPalette shoot);
	void setPossibleActionLabel();
	void setActionLabel();
	void setUpFeatureTable();
	Ui::MainWindow ui;
	GameState gameState;
	QPixmap gamePixmap;
	QPixmap simplePixmap;
	IGuiObserver* observer;
	QPalette original;
	QGraphicsScene* gameScene;
	QGraphicsScene* simpleScene;
	bool isPaused = false;
	MarioAction action;
	std::vector<MarioAction> possibleActions;
	std::vector<int> featureVector;
	std::vector<FeatureWidget*> featureWidgets;
	int state=0;
	void updateGameStateGui();
	void updateSimpleViewGui();
	void updateGameViewGui();
	void updateFeatureView();
	std::array<State, NUMBER_OF_STATES> agentStateArray;
private slots:
	void pressStartBtn();
	void pressPauseBtn();
	void pressExitBtn();
	void updateGUi();
	void loadWholeStateTable();

	
};
#endif
