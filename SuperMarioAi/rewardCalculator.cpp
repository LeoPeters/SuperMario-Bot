#include "rewardCalculator.h"
#include "MarioObject.h"
#include "Globals.h"
#include <iostream>
double RewardCalculator::calculateReward(std::vector<std::vector<int>> tempArray, MarioAction lastAction)
{
	double reward=0;
	if (tempArray.size()>0) {
		for (int y = marioPosY; y < GRIDRADIUS - 1; y++) {
			if ((lastAction == MarioAction::jump || lastAction == MarioAction::jumpRight) && simpleArray.at(y).at(marioPosX) == (int)MarioObject::empty) {
				reward = 1;
			}
			else {
				reward = 0;
			}
		}
		simpleArray = tempArray;
		calculateMarioPosition();
		updateObstacleList(calculateObstacle());
		reward += calculateObstacleReward();
		double reward2 = 0;
		for (int y = marioPosY; y < GRIDRADIUS - 1; y++) {
			if (lastAction!=MarioAction::moveLeft&& y < GRIDRADIUS - 1 && marioPosX > 0 && simpleArray.at(y + 1).at(marioPosX - 1) == (int)MarioObject::empty) {
				reward2 = 5;
			}
			else {
				reward2 = 0;
			}
		}
		reward += reward2;
	}
	return reward;
}
std::vector<Obstacle> RewardCalculator::calculateObstacle()
{
	std::vector<Obstacle> obstacleList;
	const int yStart = 12;
	bool isObstacleNew=true;
	int obstacleCount = 0;
	for(int x = 0; x < simpleArray.size(); x++) {
			if (simpleArray.at(yStart).at(x) ==(int) MarioObject::ground ) {
				if (isObstacleNew) {
					obstacleList.push_back(Obstacle());
					obstacleList[obstacleCount].left = x;
				}
				else {
					obstacleList[obstacleCount].right = x;
				}
				isObstacleNew = false;
			}
			else {
				if (!isObstacleNew ) {
					obstacleCount++;
				}
				isObstacleNew = true;
			}
	}


	return obstacleList;
}

void RewardCalculator::calculateMarioPosition() {
	for (int y = 0; y < simpleArray.size(); y++) {
		for (int x = 0; x < simpleArray.size(); x++)
			if (simpleArray.at(y).at(x) == (int)MarioObject::mario) {
				marioPosY = y;
				marioPosX = x;
			}
	}

}

void RewardCalculator::updateObstacleList(std::vector<Obstacle> obstacleList)
{
	if (obstacleList.size()==0) {
		this->obstacleList.clear();
	}
	else if(this->obstacleList.size()== obstacleList.size()){
		for (int i = 0; i < this->obstacleList.size(); i++) {
			this->obstacleList.at(i).left = obstacleList.at(i).left;
			this->obstacleList.at(i).right = obstacleList.at(i).right;
		}
	}
	else if (this->obstacleList.size() > obstacleList.size()) {
		this->obstacleList.erase(this->obstacleList.begin());
		for (int i = 0; i < this->obstacleList.size(); i++) {
			this->obstacleList.at(i).left = obstacleList.at(i).left;
			this->obstacleList.at(i).right = obstacleList.at(i).right;
		}
	}
	else if (this->obstacleList.size() < obstacleList.size()) {
		
		for (int i = 0; i < this->obstacleList.size(); i++) {
			this->obstacleList.at(i).left = obstacleList.at(i).left;
			this->obstacleList.at(i).right = obstacleList.at(i).right;
		}
		this->obstacleList.push_back(obstacleList.at(obstacleList.size()-1));
	}

	for (int i = 0; i < this->obstacleList.size(); i++) {
		if (this->obstacleList.at(i).left<=marioPosX && !this->obstacleList.at(i).marioHasArrived) {
			this->obstacleList.at(i).marioHasArrived = true;
		}
	}



}

double RewardCalculator::calculateObstacleReward()
{
	double reward = 0;
	for (int i = 0; i < this->obstacleList.size(); i++) {
		if (this->obstacleList.at(i).marioHasArrived && !this->obstacleList.at(i).rewardPaid) {
			this->obstacleList.at(i).rewardPaid = true;
			this->obstacleList.at(i).punished = false;
			reward+= REWARD_OBSTACLE_ARRIVED;
		}
		if (this->obstacleList.at(i).marioHasArrived && !this->obstacleList.at(i).punished && this->obstacleList.at(i).left>marioPosX) {
			this->obstacleList.at(i).rewardPaid = false;
			this->obstacleList.at(i).marioHasArrived = false;
			this->obstacleList.at(i).punished = true;
			reward -= REWARD_OBSTACLE_ARRIVED*1.25;

		}
	}

	return reward;
}
