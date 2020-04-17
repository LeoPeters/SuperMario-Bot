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
    void Features::calculateStateAndActions(std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state) override;
    void gameOver() override;

private:
    std::vector<std::vector<int>> marioArray;
    std::array<std::vector<int>, NUMBER_OF_STATES> states;
    std::array<int, NUMBER_OF_FEATURES> featureSize = { 2, (GRIDRADIUS / 2) + 1, GRIDRADIUS, GRIDRADIUS }; //TODO Bei mehr Features Wertebereich eintragen
    int statesSize;
    int marioPositionX;
    int marioPositionY;
    
    int isUnderBlock();
    std::array<int, 2> closestEnemy();
    int distance(int x, int y);
    int distanceToObstacleRight();
    void setMarioPosition();
    std::vector<int> getFeatureVector();
    std::vector<MarioAction> getPossibleActions();
    int Features::calculateStateNumber();
};

#endif /* MARIOSTATEFEATURES_H */

