#include "rewardCalculator.h"
#include "MarioObject.h"
#include "Globals.h"
#include <iostream>
double RewardCalculator::calculateReward(std::vector<std::vector<int>> tempArra, MarioAction lastAction)
{
	double reward=0;
	if (tempArra.size()>0) {
		simpleArray = tempArra;
		calculateMarioPosition();
		updateObstacleList(calculateObstacle());
		reward = calculateObstacleReward();
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
	for (int i = 0; i < this->obstacleList.size(); i++) {
		if (this->obstacleList.at(i).marioHasArrived && !this->obstacleList.at(i).rewardPaid) {
			this->obstacleList.at(i).rewardPaid = true;
			return REWARD_OBSTACLE_ARRIVED;
		}
	}

	return 0.0;
}
