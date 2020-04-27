/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarioStateFeatures.cpp
 * Author: MuhamadIqbal
 * 
 * Created on 12. April 2020, 00:18
 */

#include <cstdlib>
#include <iostream>
#include "Features.h"
#include "MarioObject.h"
#include "MarioAction.h"
#include "FeatureNames.h"

Features::Features() :
    marioPositionX(-1),
    marioPositionY(-1),
    statesSize(0),
    jumpBlocked(false),
    gameWon(false),
    gameLost(false),
    onGroundCounter(0),
    lastAction(MarioAction())
{
    for (int i = 0; i < (int)FeatureNames::SIZE_FEATURE_NAMES; i++) {
        featureVector.push_back(0);
    }
}

Features::~Features() {

}

std::array<std::vector<int>, NUMBER_OF_STATES> Features::getStates() {
    return states;
}

void Features::calculateStateAndActions(MarioAction lastAction, std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state, double* reward) {
    if (gameWon) {
        *reward = REWARDWIN;
        *state = 0;
        gameWon = false;
        jumpBlocked = false;
    }
    else if (gameLost) {
        *reward = REWARDLOSE;
        *state = 0;
        gameLost = false;
        jumpBlocked = false;
    } else {
        this->lastAction = lastAction;
        *reward = getReward();
        marioArray = tempArray;
        setMarioPosition();
        calculateJumpBlocked();
        *possibleActions = getPossibleActions();
        calculateFeatureVector();
        *state = calculateStateNumber();
    }
}

void Features::gameWin() {
    gameWon = true;
}

void Features::gameOver() {
    gameLost = true;
}

double Features::getReward() {
    double reward = REWARDSTEP;
    if (movedRight()) {
        reward = REWARDMOVERIGHT;
    }
    return reward;
}

bool Features::movedRight() {
    if (lastAction == MarioAction::moveRight && (featureVector[(int) FeatureNames::distanceToObstacleRight] > 1 || featureVector[(int)FeatureNames::distanceToObstacleRight] == 0)) {
        return true;
    }
    return false;
}

void Features::setMarioPosition() {
    for (int y = 0; y < GRIDRADIUS;y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            if (marioArray[y][x] == int(MarioObject::mario)) {
                marioPositionX = x;
                marioPositionY = y;
            }
        }
    }
}

std::vector<MarioAction> Features::getPossibleActions() {
    //TODO MarioAction::shoot        
    std::vector<MarioAction> possibleActions;

    possibleActions.push_back(MarioAction::moveRight);
    possibleActions.push_back(MarioAction::moveLeft);

    if (!jumpBlocked && validPosition(marioPositionY, 1, GRIDRADIUS - 2) && 
        marioArray[marioPositionY + 1][marioPositionX] == int(MarioObject::ground) &&
        marioArray[marioPositionY - 1][marioPositionX] != int(MarioObject::ground)) {
        
        possibleActions.push_back(MarioAction::jump);
        possibleActions.push_back(MarioAction::highJump);
    }
    return possibleActions;
}

int Features::isUnderBlock()
{
    if ((marioPositionY >= 1 && marioArray[marioPositionY - 1][marioPositionX] == int(MarioObject::ground)) || 
        (marioPositionY >= 2 && marioArray[marioPositionY - 2][marioPositionX] == int(MarioObject::ground)) ||
        (marioPositionY >= 3 && marioArray[marioPositionY - 3][marioPositionX] == int(MarioObject::ground))) {
        return 1;
    }
    return 0;
}

std::array<int, 2> Features::closestEnemy() {
    std::array<int, 2> closest = { GRIDRADIUS, GRIDRADIUS };
    for (int y = 0; y < marioArray.size(); y++) {
        for (int x = marioPositionX; x < marioArray.size(); x++) {
            if (marioArray[y][x] == (int)MarioObject::enemy && distance(closest[0], closest[1]) >= distance(x, y)) {
                closest = { x, y };
            }
        }
    }
    if (closest[0] == GRIDRADIUS && closest[1] == GRIDRADIUS) {
        //TODO Maybe this is bad. If the enemy is in the bottom right corner this will return (0,0) as if there was no enemy
        closest = { 0, 0 };
    }
    else {
        closest = { std::abs(marioPositionX - closest[0]) + std::abs(marioPositionY - closest[1]) };
    }
    return closest;
}

int Features::distance(int x, int y) {
    return std::abs(marioPositionX - x) + std::abs(marioPositionY - y);
}

int Features::distanceToObstacleRight() {
    int distance = 0;
    for (int x = marioPositionX; x < GRIDRADIUS; x++) {
        if (marioArray[marioPositionY][x] == (int)MarioObject::ground) {
            distance = x - marioPositionX;
            return distance;
        }
    }
    //std::cout << "Distance: " << distance << " MarioPositionX: " << marioPositionX << std::endl;
    return distance;
}

void Features::calculateFeatureVector() {
    std::vector<int> features;
    std::array<int, 2> closest = closestEnemy();

    features.push_back(isUnderBlock());
    features.push_back(closest[0]); //X
    features.push_back(closest[1]); //Y
    features.push_back(distanceToObstacleRight());
    
    featureVector = features;
}

int Features::calculateStateNumber() {
    std::vector<int> state = featureVector;
    for (int i = 1; i <= statesSize; i++) {
        if (states[i] == state) {
            return i;
        }
    }
    states[statesSize++] = state;
    return statesSize;
}

void Features::calculateJumpBlocked()
{
    if (validPosition(marioPositionY, 0, GRIDRADIUS - 2) &&
        marioArray[marioPositionY + 1][marioPositionX] == int(MarioObject::ground)){
        onGroundCounter++;
    } else {
        onGroundCounter = 0;
    }
    if (onGroundCounter >= 0) {
        jumpBlocked = false;
    } else {
        jumpBlocked = true;
    }
}

bool Features::validPosition(int value, int lowBorder, int highBorder) {
    return (value >= lowBorder && value <= highBorder);
}

std::vector<int> Features::getFeatureVector(int index) {
    return states[index];
}