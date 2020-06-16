#pragma once
#include "MarioAction.h"
#include <vector>
#include <array>
#include "Obstacle.h"
class RewardCalculator
{
public :
    double calculateReward(std::vector<std::vector<int>> tempArra,MarioAction lastAction);
    void setProgess(int i);
    int getProgress();
private:
    int marioPosX;
    int marioPosY;
    int progress=0;

    std::vector<Obstacle> obstacleList;
    MarioAction lastAction;
    std::vector<std::vector<int>> gameArray;
    std::vector<std::vector<int>> lastGameArray;
    std::vector<Obstacle> calculateObstacle();
    void calculateMarioPosition();
    void updateObstacleList(std::vector<Obstacle> obstacleList);
    double calculateObstacleReward();
    void calculateProgress();
    bool isStaticObject(int objectIndex);

};

