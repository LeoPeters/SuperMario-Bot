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
#include "Features.h"
#include "MarioObject.h"
#include "MarioAction.h"
#include <iostream>
Features::Features() :
    marioPositionX(-1),
    marioPositionY(-1),
    statesSize(0),
    jumpBlocked(false)
{

}

Features::~Features() {

}


void Features::calculateStateAndActions(std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state) {
    marioArray = tempArray;
    setMarioPosition();
    calculateJumpBlocked();
    *possibleActions = getPossibleActions();
    *state = calculateStateNumber(); 
}

void Features::gameOver() {

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

    if (marioPositionX != 0 && marioArray[marioPositionY][marioPositionX - 1] != int(MarioObject::ground)) {
        possibleActions.push_back(MarioAction::moveLeft);
    }

    //No boundaries needed. Mario can max be at X position (GRIDRADIUS/2 + 1)
    if (marioArray[marioPositionY][marioPositionX + 1] != int(MarioObject::ground)) {
        possibleActions.push_back(MarioAction::moveRight);
    }

    if (!jumpBlocked && 
        marioArray[marioPositionY + 1][marioPositionX] == int(MarioObject::ground) && 
        marioArray[marioPositionY - 1][marioPositionX] != int(MarioObject::ground)) {
        
        possibleActions.push_back(MarioAction::jump);
        possibleActions.push_back(MarioAction::highJump);
    }



    return possibleActions;
}

int Features::isUnderBlock(){
	//TODO Wertebereich
    if ((marioPositionY >= 1 && marioArray[marioPositionY - 1][marioPositionX] == int(MarioObject::ground)) || 
        (marioPositionY >= 2 && marioArray[marioPositionY - 2][marioPositionX] == int(MarioObject::ground)) ||
        (marioPositionY >= 2 && marioArray[marioPositionY - 3][marioPositionX] == int(MarioObject::ground))) {
        return 1;
    }
    else{
        return 0;
    }
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
    return closest;
}

int Features::distance(int x, int y) {
    return std::abs((marioPositionX + marioPositionY) - (x + y));
}

int Features::distanceToObstacleRight() {
    int distance = 0;
    for (int x = marioPositionX; x < GRIDRADIUS; x++) {
        if (marioArray[marioPositionY][x] == (int)MarioObject::ground) {
            distance =  x - marioPositionX;
        }
    }
    return distance;
}

std::vector<int> Features::getFeatureVector() {
    std::vector<int> state;
    std::array<int, 2> closest = closestEnemy();

    state.push_back(isUnderBlock());
    state.push_back(closest[0]); //X
    state.push_back(closest[1]); //Y
    state.push_back(distanceToObstacleRight());
    
    return state;
}

int Features::calculateStateNumber() {
    std::vector<int> state = getFeatureVector();
    for (int i = 0; i < NUMBER_OF_STATES; i++) {
        if (states[i] == state) {
            statesSize++;
            return i;
        }
    }
    states[statesSize] = state;
    return statesSize;
}

void Features::calculateJumpBlocked()
{
    if (marioArray[marioPositionY + 1][marioPositionX] == int(MarioObject::ground)){
        onGroundCounter++;
    }
    else {
        onGroundCounter = 0;
    }
    if (onGroundCounter >= 0) {
        jumpBlocked = false;
    }
    else {
        jumpBlocked = true;
    }
    
}

/*
int Features::distanceToEnemyX(){
    // possible x : -2,-1,0,1,2
    // Anfang vom feld
    int startX = marioPositionX - (2 * marioPositionX);
    for (int x = marioPositionX; x < GRIDRADIUS; x++){
        if (marioArray[marioPositionY][x] == int(MarioObject::enemy)){
            return x + startX;
        }
    }
    for (int y = 0; y < GRIDRADIUS;y++){
        for (int x = (GRIDRADIUS - 1); x >= 0; x--){
            if (marioArray[y][x] == int(MarioObject::enemy)){
                return x + startX;
            }
        }
    }
    return -99;
}
*/

/*
int Features::distanceToEnemyY(){
    int startY = (GRIDRADIUS /2)* -1;
     for (int x = marioPositionX; x < GRIDRADIUS; x++){
        if (marioArray[marioPositionY][x] == int(MarioObject::enemy)){
            return marioPositionY + startY;
        }
    }

    for (int y = 0; y < GRIDRADIUS;y++){
        for (int x = (GRIDRADIUS - 1); x >= 0; x--){
            if (marioArray[y][x] == int(MarioObject::enemy)){
                return (y + startY);
            }
        }
    }
    // not found
    return -99;
}

int Features::distanceToObstacle() {
    // possible x : -2,-1,0,1,2
    // Anfang von feld
    int startX = marioPositionX - (2 * marioPositionX);

    for (int x = marioPositionX; x < GRIDRADIUS; x++){
        if (marioArray[marioPositionY][x] == int(MarioObject::ground)){
            return x + startX;
        }
    }
    // not found
    return -99;
}
*/