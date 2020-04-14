#pragma once

#include <QMainWindow>
#include "IGuiObserver.h"
#include "ActionEnum.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow(IGuiObserver* observer);
	~MainWindow();
	bool isActivated();
	void updateGameView(HBITMAP);
	void updateSimplifyView(std::vector<std::vector<int>> simpleView);
	void updateAction(Action nextAction);
	void updateState(int);
	bool getIsPaused();

private:
	QImage generateSimpleImage(std::vector<std::vector<int>> simpleView);
	Ui::MainWindow ui;
	IGuiObserver* observer;
	QPalette original;
	const QRgb marioColor = qRgb(255, 49, 32);
	const QRgb skyColor= qRgb(146, 144, 255);
	const QRgb blockColor = qRgb(153, 78, 0);
	const QRgb enemyColor = qRgb(0, 0, 0);
	const QRgb itemColor = qRgb(255, 245, 57);
	bool isPaused = false;
private slots:
	void pressStartBtn();
	void pressPauseBtn();
};
