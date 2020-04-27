/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MarioStateFeatures.h
 * Author: MuhamadIqbal
 *
 * Created on 12. April 2020, 00:18
 */

#ifndef MARIOSTATEFEATURES_H
#define MARIOSTATEFEATURES_H

#include <vector>
#include <array>
#include "Globals.h"
#include "IEnvironment.h"


class Features : public IEnvironment {
public:
    Features();
    ~Features();
    void Features::calculateStateAndActions(MarioAction lastAction, std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state, double* reward) override;
    std::array<std::vector<int>, NUMBER_OF_STATES> getStates() override;
    void gameOver() override;
    void gameWin() override;
    std::vector<int> getFeatureVector(int i) override;


private:
    std::vector<std::vector<int>> marioArray;
    std::array<std::vector<int>, NUMBER_OF_STATES> states;
    std::vector<int> featureVector;
    int statesSize;
    int marioPositionX;
    int marioPositionY;
    bool jumpBlocked;
    int onGroundCounter;
    bool gameWon;
    bool gameLost;
    MarioAction lastAction;
    
    bool validPosition(int value, int lowBorder, int highBorder);
    int isUnderBlock();
    std::array<int, 2> closestEnemy();
    int distance(int x, int y);
    int distanceToObstacleRight();
    void setMarioPosition();
    void calculateFeatureVector();
    std::vector<MarioAction> getPossibleActions();
    int Features::calculateStateNumber();
    void Features::calculateJumpBlocked();
    // NEW Features
    int Features::isJump(); 
    int Features::getNumberOfEnemy(); 
    int Features::marioStatus();
    int Features::isItemNearby();
    std::array<int, 2> closestItems(); 
    int distanceToHoleRight();
    double getReward();
    bool Features::movedRight();
    bool Features::movedRight();
};

#endif /* MARIOSTATEFEATURES_H */

