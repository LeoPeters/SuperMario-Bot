#ifndef mainwindow_h
#define mainwindow_h
#include <QMainWindow>
#include "IGuiObserver.h"
#include "MarioAction.h"
#include <QStandardItemModel>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(IGuiObserver*);
	~MainWindow();
	bool isActivated();
	void setUpTable();
	void setAction(MarioAction nextAction);
	void setPossibleAction(std::vector<MarioAction> nextAction);
	void setState(int);
	bool getIsPaused();
	void setGamePixmap(QPixmap);
	void setSimplePixmap(QPixmap);
signals:
	void updateView();

private:
	void setActionLabelPalette(QPalette jump, QPalette left, QPalette right, QPalette highJump, QPalette shoot);
	void setPossibleActionLabel();
	void setActionLabel();
	Ui::MainWindow ui;
	QPixmap gamePixmap;
	QPixmap simplePixmap;
	IGuiObserver* observer;
	QPalette original;
	QGraphicsScene* gameScene;
	QGraphicsScene* simpleScene;
	bool isPaused = false;
	MarioAction action;
	std::vector<MarioAction> possibleActions;
	int state=0;
private slots:
	void pressStartBtn();
	void pressPauseBtn();
	void pressExitBtn();
	void updateGUi();
};
#endif
