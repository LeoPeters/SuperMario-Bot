#pragma once
#include <array>
#include <vector>
#include "MarioAction.h"

class Features
{
public:
    Features();
    ~Features();

    int isUnderBlock();
    std::array<int, 2> closestEnemy();
    int distanceToObstacle();
    void setMarioPosition();
    //bool isJumping(); 
    int getNumberOfEnemies();
    bool isItemAvailable();
    std::array<int, 2> closestItem();
    int distanceToHole();
    void setMarioArray(std::vector<std::vector<int>> &marioArray);
    void calculateJumpBlocked(MarioAction);
    std::vector<MarioAction> getPossibleActions();
    void setJumpBlocked(bool jumpBlocked);

private:
    bool jumpBlocked;
    int onGroundCounter;
    std::vector<std::vector<int>> marioArray;
    int marioPositionX;
    int marioPositionY;

    bool validPosition(int value, int lowBorder, int highBorder);
    int distance(int x, int y);
    bool conqueredObstacle();

};