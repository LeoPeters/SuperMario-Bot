#pragma once
#include <vector>
#include <Windows.h>
#include <string>
#include <QPixMap>
#include "Globals.h"
#include "GameState.h"
#include "MarioFeature.h"
#include "State.h"
class AiData
{
private:
	QPixmap generateSimpleView(std::vector<std::vector<int>> simpleView);


//setter
public:
	QPixmap getSimpleView();
	QPixmap getGameView();

	void reset();


//constants
private:
	const static int emptyValue = SKY;
	const static int marioValue = MARIO;
	const static int groundValue = BLOCK;
	const static int enemyValue = ENEMY;
	const static int itemValue = ITEM;
	const static int finishFlagValue = WINNINGCONDS;
//colorValues
private:
	const QRgb red = qRgb(255, 49, 32);
	const QRgb skyBlue = qRgb(146, 144, 255);
	const QRgb brown = qRgb(153, 78, 0);
	const QRgb black = qRgb(0, 0, 0);
	const QRgb yellow = qRgb(255, 245, 57);
	const QRgb darkGreen = qRgb(53, 84, 0);

//variable
public:
	std::vector<std::string> actionList;
	std::vector<int> featureValues;
	std::vector<int> lastFeatureValues;
	std::vector<MarioAction> possibleActions;
	std::vector<MarioFeature> activeFeatures;
	std::vector<std::vector<int>> simpleView;
	HBITMAP gameView;
	GameState gameState;
	State agentState;
	State lastAgentState;
	MarioAction nextAction;
	std::vector<int> stateNumberQueue;
	int agentStateNumber = 0;
	int loopTime = 0;
	int loopCounter = 0;
	int marioDeathCounter = 0;
	int marioWinCounter = 0;
	double reward = 0;
};
