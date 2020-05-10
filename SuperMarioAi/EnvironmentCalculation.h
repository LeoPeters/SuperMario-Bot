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
#include "Features.h"
#include "rewardCalculator.h"


class EnvironmentCalculation : public IEnvironment {
public:
    EnvironmentCalculation();
    ~EnvironmentCalculation();
    void calculateStateAndActions(MarioAction lastAction, std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state, double* reward) override;
    std::array<std::vector<int>, NUMBER_OF_STATES>* getStates() override;
    void gameOver() override;
    void gameWin() override;
    std::vector<int> getFeatureVector(int i) override;
    int getStatesSize() override;
    void setStatesSize(int statesSize) override;
private:
    Features features;
    std::array<std::vector<int>, NUMBER_OF_STATES> states;
    std::vector<int> featureVector;
    int statesSize;
    bool gameWon;
    bool gameLost;
    MarioAction lastAction;
    RewardCalculator calc;
    void calculateFeatureVector();
    int calculateStateNumber();
    double getReward(std::vector<std::vector<int>> tempArray);
    bool movedRight();
    bool validPosition(int value, int lowBorder, int highBorder);
};

#endif MARIOSTATEFEATURES_H

