#pragma once
struct Obstacle
{
public:
	int right = 0;
	int left = 0;
	bool marioHasArrived = false;
	bool rewardPaid = false;
	int arrivedCounter = 0;
};

