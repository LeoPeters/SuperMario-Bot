#ifndef SUPERMARIOBOT_SRC_QLEARNING_QLEARNING_H_
#define SUPERMARIOBOT_SRC_QLEARNING_QLEARNING_H_

#include <vector>
#include <array>
#include "State.h"

class QLearning {
public:
	QLearning();
	~QLearning();

	const static int NUMBER_OF_STATES = 20;
	enum Action {
		LEFT, RIGHT, JUMP, RUN, ACTION_MAX
	};

	enum Policy {
		GREEDY, SOFT, SOFTMAX
	};

	Action runState(int stateIndex, std::vector<Action, bool> action);

private:
	std::array<State, NUMBER_OF_STATES> scores;
};

#endif