#pragma once
#include "MarioAction.h"
#include <vector>
#include <array>
#include "Obstacle.h"
class RewardCalculator
{
public :
    double calculateReward(std::vector<std::vector<int>> tempArra);
private:
    int marioPosX;
    int marioPosY;
    std::array<Obstacle,3> obstacleArray;
    MarioAction lastAction;
    std::vector<std::vector<int>> simpleArray;
    void calculateObstacle();
    void calculateMarioPosition();

};

