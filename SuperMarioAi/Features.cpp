

#include <cstdlib>
#include "Features.h"
#include "MarioObject.h"
#include "MarioAction.h"
#include <iostream>


void debugArray(std::vector<std::vector<int>> tempArray);

Features::Features() :
    marioPositionX(-1),
    marioPositionY(-1),
    statesSize(0),
    jumpBlocked(false)
{

}

Features::~Features() {

}

std::array<std::vector<int>, NUMBER_OF_STATES> Features::getStates() {
    return states;
}

void Features::calculateStateAndActions(std::vector<std::vector<int>> tempArray, std::vector<MarioAction>* possibleActions, int* state) {
    marioArray = tempArray;
    setMarioPosition();
    calculateJumpBlocked();
    *possibleActions = getPossibleActions();
    *state = calculateStateNumber(); 

    
}


void Features::setMarioPosition() {
    for (int y = 0; y < GRIDRADIUS;y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            if (marioArray[y][x] == int(MarioObject::mario)) {
                marioPositionX = x;
                marioPositionY = y;

                std::cout << std::endl << "XMario:" << x << " YMario:" << y << std::endl;
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

    //std::cout << std::endl << "X:" << closest[0] << " Y:" << closest[1] << std::endl;

    return closest;
}

int Features::distance(int x, int y) {
    return std::abs(marioPositionX - x) + std::abs(marioPositionY - y);
}

int Features::distanceToObstacleRight() { 
    int distance = 0;
    for (int x = 0; x < GRIDRADIUS; x++) {
        if (marioArray[marioPositionY][x] == (int)MarioObject::ground) {
            distance =  x - marioPositionX - 1;
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
    for (int i = 1; i <= statesSize; i++) {
        if (states[i] == state) {
            statesSize++;
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

// NEW FEATURES


int Features::isJump() {

    if (marioArray[marioPositionY + 1][marioPositionX] != int(MarioObject::ground) &&
        marioArray[marioPositionY + 1][marioPositionX] != int(MarioObject::item)) 
    {
        return 1;
    }
    return 0;
}

int Features::getNumberOfEnemy() {
    
    int numberOfEnemy = 0;

    for (int y = 0; y < GRIDRADIUS; y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            if (marioArray[y][x] == int(MarioObject::enemy)) {
                numberOfEnemy++;
            }
        }
    }

    return numberOfEnemy;
    
}

int Features::isItemNearby() {
    
    for (int y = 0; y < GRIDRADIUS; y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            if (marioArray[y][x] == int(MarioObject::enemy)) {
                return 1;
            }
        }
    }

    return 0;

}

int Features::distanceToHoleRight() {
    
    int distance = 0;
  
    // feststellen, dass Mario auf dem Boden ist
    if (marioPositionY == GRIDRADIUS - 3) {
        
        // nach Loch suchen
        for (int x = marioPositionX; x < GRIDRADIUS; x++) {
            if (marioArray[marioPositionY + 1][x] == int(MarioObject::empty) 
                && marioArray[marioPositionY + 2][x] == int(MarioObject::empty)) {
                
                distance = x - marioPositionX;
                return distance;
            }
        }
        return distance;
    
    }

}

std::array<int, 2> Features::closestItems() {
    
    std::array<int, 2> closestItem = { 0, 0 };
    
    for (int y = 0; y < marioArray.size(); y++) {
        for (int x = marioPositionX; x < marioArray.size(); x++) {
            if (marioArray[y][x] == (int)MarioObject::item && distance(closestItem[0], closestItem[1]) >= distance(x, y)) {
                closestItem = { x, y };
            }
        }
    }
        
    return closestItem;
}

int Features::marioStatus() {
    //TODO
    return 0;
}









