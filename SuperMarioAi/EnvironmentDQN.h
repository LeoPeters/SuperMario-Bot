#pragma once
#include <vector>
#include "GameState.h"
class EnvironmentDQN
{
public:
	EnvironmentDQN();
	void calculateEnv(std::vector<std::vector<int>> vec, GameState gameState);
	void initDQNInput();
	double getReward();
	std::vector<unsigned char> getInputDQN();
	bool getDone();
private:
	std::vector<unsigned char> flattingVector(std::vector<std::vector<int>> vec);
	void generateDQNInput(std::vector<unsigned char> flatVec);
	void calculateReward();
	bool progressStep();
	bool isStaticObject(int i);

private:
	std::vector<std::vector<int>> simpleVec;
	std::vector<std::vector<int>> lastSimpleVec;
	std::vector<unsigned char> dqnInput;
	GameState gameState;
	bool done;
	double reward;
};

