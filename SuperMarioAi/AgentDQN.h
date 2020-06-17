#pragma once
#include "MarioAction.h"
#include <vector>
#include "GameState.h"
#include "DQNAgent.h"
#include "EnvironmentDQN.h"
class AgentDQN
{
public:
	AgentDQN();
	MarioAction calculateAction(EnvironmentDQN env);

private:
	bool madeStep;
	std::vector<unsigned char> input;
	MarioAction action;
	DQNAgent agent;
};

