#include "rewardCalculator.h"
#include "MarioObject.h"
#include <iostream>
double RewardCalculator::calculateReward(std::vector<std::vector<int>> tempArra)
{
	if (tempArra.size()>0) {
		simpleArray = tempArra;
		calculateMarioPosition();
		calculateObstacle();
	}
	return 0.0;
}
void RewardCalculator::calculateObstacle()
{
	for (int i = 0; i < obstacleArray.size(); i++) {
		obstacleArray.at(i).isVisible = false;
	}
	const int yStart = 12;
	bool isObstacleNew=true;
	int obstacleCount = 0;
	for(int x = 0; x < simpleArray.size(); x++) {
			if (simpleArray.at(yStart).at(x) ==(int) MarioObject::ground ) {
				if (isObstacleNew) {
					obstacleArray[obstacleCount].left = x;
					obstacleArray.at(obstacleCount).isVisible = true;
				}
				else {
					obstacleArray[obstacleCount].right = x;
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

	for (int i = 0; i < obstacleArray.size(); i++) {

	}
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