#include "DeepQNetwork.h"

DeepQNetwork::DeepQNetwork(float lr, int actions) :learnrate(lr),n_actions(actions),model(),
optimizer(model.parameters(), lr),loss()
{
	
}

DeepQNetwork::~DeepQNetwork() = default;
