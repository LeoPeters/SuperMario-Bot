

#include <cstdlib>
#include <iostream>
#include "EnvironmentCalculation.h"
#include "MarioObject.h"
#include "MarioAction.h"
#include "MarioFeature.h"
#include "Features.h"
#include "rewardCalculator.h"

EnvironmentCalculation::EnvironmentCalculation() :
    statesSize(1),
    gameWon(false),
    gameLost(false),
    lastAction(MarioAction()),
    features(Features())
{
    for (int i = 0; i < MarioFeature::size; i++) {
        featureVector.push_back(0);
    }
}

EnvironmentCalculation::~EnvironmentCalculation() 
{

}

std::array<std::vector<int>, NUMBER_OF_STATES>* EnvironmentCalculation::getStates() 
{
    return &states;
}

int EnvironmentCalculation::getStatesSize()
{
    return statesSize;
}

void EnvironmentCalculation::setStatesSize(int statesSize)
{
    this->statesSize = statesSize;
}

void EnvironmentCalculation::calculateStateAndActions(MarioAction lastAction, std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state, double* reward) 
{
    if (gameWon) 
    {
        *reward = REWARDWIN;
        *state = 0;
        gameWon = false;
        features.setJumpBlocked(false);
    }
    else if (gameLost) 
    {
        *reward = REWARDLOSE;
        *state = 0;
        gameLost = false;
        features.setJumpBlocked(false);
    } else {
        this->lastAction = lastAction;
        *reward = getReward(tempArray);
        features.setMarioArray(tempArray);
        features.setMarioPosition();
        features.calculateJumpBlocked(lastAction);
        *possibleActions = features.getPossibleActions();
        calculateFeatureVector();
        *state = calculateStateNumber();
    }
}

void EnvironmentCalculation::gameWin() 
{
    gameWon = true;
}

void EnvironmentCalculation::gameOver() 
{
    gameLost = true;
}

double EnvironmentCalculation::getReward(std::vector<std::vector<int>> tempArray)
{
    RewardCalculator calc;
    calc.calculateReward(tempArray);
    double reward = 0;
    if (lastAction == MarioAction::moveRight && (featureVector[(int)MarioFeature::distanceToObstacle] == 1)) {
        reward = -1.5;
    }

    if (!features.canMoveLeft()) {
        reward -= 2;
    }

//    if (features.distanceToObstacle() > 1 && lastAction == MarioAction::moveRight ) {
//        reward += 0.8;
//    }

    return reward;
}

bool EnvironmentCalculation::movedRight() 
{
    if (lastAction == MarioAction::moveRight && (featureVector[(int) MarioFeature::distanceToObstacle] > 1 || featureVector[(int)MarioFeature::distanceToObstacle] == 0)) {
        return true;
    }
    return false;
}


void EnvironmentCalculation::calculateFeatureVector() 
{
    std::vector<int> featureVector;
    std::array<int, 2> closestEnemy = features.closestEnemy();
    std::array<int, 2> closestItem = features.closestItem();

    int temp = features.distanceToHole();
    for (int i = 0; i < MarioFeature::size; i++) 
    {
        switch (i)
        {
        case (int)MarioFeature::closestEnemyX:
            featureVector.push_back(closestEnemy[0]); //X
            break;
        case (int)MarioFeature::closestEnemyY:
            featureVector.push_back(closestEnemy[1]); //Y
            break;
        //case (int)MarioFeature::isUnderBlock:
        //    featureVector.push_back(features.isUnderBlock());
        //    break;
        case (int)MarioFeature::distanceToObstacle:
            featureVector.push_back(features.distanceToObstacle());
        break;
        /*case (int)MarioFeature::numberOfEnemies:
            featureVector.push_back(features.getNumberOfEnemies());
            break;*/
        
        case (int)MarioFeature::distanceToHole:
            
            featureVector.push_back(temp);
            break;
        case (int)MarioFeature::isJumping:
            featureVector.push_back(features.isJumping(lastAction));
            break;
        case (int)MarioFeature::obstacleHeight:
            featureVector.push_back(features.obstacleHeight());
            break;
        /*case (int)MarioFeature::itemAvailable:
                featureVector.push_back(features.isItemAvailable());
                break;
        case (int)MarioFeature::closestItemX:
            featureVector.push_back(closestItem[0]);
            break;

        case (int)MarioFeature::closestItemY:
            featureVector.push_back(closestItem[1]);
            break;*/
        default:
            break;
        }
    }
    this->featureVector = featureVector;
}


int EnvironmentCalculation::calculateStateNumber() 
{
    std::vector<int> state = featureVector;
    for (int i = 1; i < statesSize; i++) {
        if (states[i] == state) {
            return i;
        }
    }
    states[statesSize] = state;
    return statesSize++;
}

bool EnvironmentCalculation::validPosition(int value, int lowBorder, int highBorder) 
{
    return (value >= lowBorder && value <= highBorder);
}

std::vector<int> EnvironmentCalculation::getFeatureVector(int index) {
    return states[index];
}