#ifndef aigui_h
#define aigui_h
#include "ScreenCapture.h"
#include "MarioAction.h"
#include "MainWindow.h"

class AiGui
{
public:
	AiGui(int argc, char** argv, IGuiObserver*);
	void runGui();
	void end();
	void update();
	MainWindow* getMainWindow();
	IGuiObserver* getObserver();
private:
	MainWindow* mWindow;
	QApplication* app;
	IGuiObserver* observer;
	QImage generateSimpleImage(std::vector<std::vector<int>> simpleView);
	const QRgb marioColor = qRgb(255, 49, 32);
	const QRgb skyColor = qRgb(146, 144, 255);
	const QRgb blockColor = qRgb(153, 78, 0);
	const QRgb enemyColor = qRgb(0, 0, 0);
	const QRgb itemColor = qRgb(255, 245, 57);
	const QRgb winningColor = qRgb(53, 84, 0);

};
#endif

