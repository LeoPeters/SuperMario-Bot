#include "AgentDQN.h"
#include <iostream>
#include "Globals.h"

AgentDQN::AgentDQN():
	agent(DQNAgent( /*gamma*/0.999, /*epsilon*/0.1, /*learnrate*/0.001,
		/*eps_min*/0.001, /*eps_dec*/0.0001, /*mem_size*/10000,
		/*batch_size*/16, /*update_target*/10, /*actions*/12,
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
	}
	madeStep = true;
	input = env.getInputDQN();
	int actionIndex = agent.choose_action(input);
	action = MarioAction(actionIndex);
	return action;
}
