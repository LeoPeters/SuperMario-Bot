#include "Features.h"
#include "Globals.h"
#include "MarioObject.h"
#include "MarioAction.h"
#include<iostream>
Features::Features() :
    marioPositionX(-1),
    marioPositionY(-1),
    jumpBlocked(false), 
    onGroundCounter(0)
{

}

Features::~Features()
{

}

void Features::setMarioPosition()
{
    for (int y = 0; y < GRIDRADIUS;y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            if (marioArray[y][x] == int(MarioObject::mario)) {
                marioPositionX = x;
                marioPositionY = y;
            }
        }
    }
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

std::array<int, 2> Features::closestEnemy()
{
    std::array<int, 2> closest = { GRIDRADIUS, GRIDRADIUS };
    if (marioArray.size() > 0) {

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
        closest = { std::abs(marioPositionX - closest[0]), std::abs(marioPositionY - closest[1]) };
    }
    }
    //std::cout << std::endl << "X:" << closest[0] << " Y:" << closest[1] << std::endl;
    return closest;
}

int Features::distance(int x, int y)
{
    return std::abs(marioPositionX - x) + std::abs(marioPositionY - y);
}

int Features::distanceToObstacle()
{
        int distance = 0;
    if (marioArray.size() > 0) {
        for (int x = marioPositionX; x < GRIDRADIUS; x++) {
            if (marioArray[marioPositionY][x] == (int)MarioObject::ground) {
                distance = x - marioPositionX;
                return distance;
            }
        }
    }
    //std::cout << "Distance: " << distance << " MarioPositionX: " << marioPositionX << std::endl;
    return distance;
}


bool Features::isJumping(MarioAction lastAction)
{
    if (marioPositionY> GRIDRADIUS-2) {
        return true;
    }
    if (validPosition(marioPositionY, 0, GRIDRADIUS - 2) &&
        lastAction==MarioAction::jump ||marioArray[(marioPositionY + 1)][marioPositionX] != int(MarioObject::ground))
    {
        return true;
    }
    return false;
}
bool Features::canMoveLeft()
{

    if (validPosition(marioPositionY, 0, GRIDRADIUS - 2) )
    {
        for (int i = 0; i < GRIDRADIUS; i++) {
            if (marioArray[i][0] == (int)MarioObject::mario) {

            return false;
            }
        }
        if (marioPositionX == 0) {
            return false;
        }
    }
    
    return true;
}



int Features::getNumberOfEnemies() {
    int numberOfEnemies = 0;

    for (int y = 0; y < GRIDRADIUS; y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            if (marioArray[y][x] == int(MarioObject::enemy)) {
                numberOfEnemies++;
                if (numberOfEnemies >= MAX_NUMBER_ENEMIES) {
                    return numberOfEnemies;
                }
            }
        }
    }
    return numberOfEnemies;
}

bool Features::isItemAvailable()
{
    for (int y = 0; y < GRIDRADIUS; y++) {
        for (int x = 0; x < GRIDRADIUS; x++) {
            if (marioArray[y][x] == int(MarioObject::item)) {
                return true;
            }
        }
    }
    return false;
}

int Features::distanceToHole()
{
    for (int x = marioPositionX+1; x < GRIDRADIUS; x++)
    {
        if (marioArray[marioPositionY][x] != (int)MarioObject::ground)
        {
            for (int y = marioPositionY + 1; y < GRIDRADIUS; y++)
            {
                if (marioArray[y][x] == (int)MarioObject::ground)
                {
                    break;
                }
                if (y == GRIDRADIUS - 1)
                {
                    return x - marioPositionX;
                }
            }
        }
    }
    return 0;
}

std::array<int, 2> Features::closestItem() {
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

void Features::calculateJumpBlocked(MarioAction lastAction)
{

    if (lastAction == MarioAction::jump || lastAction == MarioAction::jumpRight) {
        onGroundCounter++;
    }else {
        onGroundCounter = 0;
    }
   
    if (onGroundCounter < 8) {
        jumpBlocked = false;
    }
    else {
        jumpBlocked = true;
    }
}

int Features::getEnemyIsLeft() {
    for (int y = 0; y < GRIDRADIUS; y++) {
        if (marioPositionX > 0 && marioArray[y][marioPositionX - 1] == (int)MarioObject::enemy) {
            return 1;
        }
        if (marioPositionX > 1 && marioArray[y][marioPositionX - 2] == (int)MarioObject::enemy) {
        }
    }
    return 0;
}
int Features::getHoleIsLeft() {
    if (marioPositionX > 0 && marioPositionY < GRIDRADIUS-1) {
        if (marioArray[(marioPositionY+1)][(marioPositionX )]==(int)MarioObject::ground && marioArray[(marioPositionY + 1)][(marioPositionX-1)] == (int)MarioObject::empty) {
            return 1;
        }
    }
    return 0;
}

int Features::getRightFromObstacle(){

        for (int x = 0; x < marioPositionX; x++) {
            if (marioArray[marioPositionY][x] == (int)MarioObject::ground) {
                return 1;
            }
    }
    return 0;

}
std::vector<MarioAction> Features::getPossibleActions()
{
    //TODO MarioAction::shoot        
    std::vector<MarioAction> possibleActions;

    possibleActions.push_back(MarioAction::moveRight);
    possibleActions.push_back(MarioAction::moveLeft);
    if (!jumpBlocked) {

    possibleActions.push_back(MarioAction::jump);
    possibleActions.push_back(MarioAction::jumpRight);

    }
    //    marioArray[marioPositionY + 1][marioPositionX] == int(MarioObject::ground) &&
    //    marioArray[marioPositionY - 1][marioPositionX] != int(MarioObject::ground)) 
    //if (!jumpBlocked && validPosition(marioPositionY, 1, GRIDRADIUS - 2) &&
    //    marioArray[marioPositionY + 1][marioPositionX] == int(MarioObject::ground) &&
    //    marioArray[marioPositionY - 1][marioPositionX] != int(MarioObject::ground)) {

    //    possibleActions.push_back(MarioAction::jump);
    //    possibleActions.push_back(MarioAction::highJump);
    //}
    return possibleActions;
}

void Features::setJumpBlocked(bool jumpBlocked)
{
    this->jumpBlocked = jumpBlocked;
}

int Features::obstacleHeight()
{
    int obstacleX = marioPositionX + distanceToObstacle();
    int obstacleHeight= marioPositionY;
    while (obstacleHeight > 0 && marioArray[obstacleHeight][obstacleX]== (int)MarioObject::ground) {
        obstacleHeight--;
    }
    obstacleHeight -= marioPositionY;
    obstacleHeight *= -1;
    return obstacleHeight;
}

bool Features::validPosition(int value, int lowBorder, int highBorder)
{
    if(marioArray.size()<1){
        return false;
    }
    return (value >= lowBorder && value <= highBorder);
}

void Features::setMarioArray(std::vector<std::vector<int>>& marioArray)
{
    this->marioArray = marioArray;
}
