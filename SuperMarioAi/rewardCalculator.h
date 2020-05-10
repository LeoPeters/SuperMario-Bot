#pragma once
#include "MarioAction.h"
#include <vector>
#include <array>
#include "Obstacle.h"
class RewardCalculator
{
public :
    double calculateReward(std::vector<std::vector<int>> tempArra,MarioAction lastAction);
private:
    int marioPosX;
    int marioPosY;
    std::vector<Obstacle> obstacleList;
    MarioAction lastAction;
    std::vector<std::vector<int>> simpleArray;
    std::vector<Obstacle> calculateObstacle();
    void calculateMarioPosition();
    void updateObstacleList(std::vector<Obstacle> obstacleList);
    double calculateObstacleReward();

};

