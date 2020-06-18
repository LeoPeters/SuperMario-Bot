#include "AgentDQN.h"
#include <iostream>
#include "Globals.h"

AgentDQN::AgentDQN():
	agent(DQNAgent( /*gamma*/0.999, /*epsilon*/0.20, /*learnrate*/0.0001,
		/*eps_min*/0.03, /*eps_dec*/0.005, /*mem_size*/100000,
		/*batch_size*/16, /*update_target*/20, /*actions*/12,
		/*input_shape: DIM, HEIGHT, WIDTH*/4, 15, 15)),
	madeStep(false),
	action(0)
{
	
}

MarioAction AgentDQN::calculateAction(EnvironmentDQN env)
{
	if (madeStep) {
		agent.store_transition(input, (int)action, env.getReward(), env.getInputDQN(), env.getDone());
		agent.learn();
		if ((int)env.getReward() == REWARDWIN) {
			agent.saveStateAfterWin();
		}
	}
	madeStep = true;
	input = env.getInputDQN();
	int actionIndex = agent.choose_action(input);
	action = MarioAction(actionIndex);
	return action;
}
