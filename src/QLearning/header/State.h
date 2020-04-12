#ifndef SUPERMARIOBOT_SRC_QLEARNING_HEADER_STATE_H_
#define SUPERMARIOBOT_SRC_QLEARNING_HEADER_STATE_H_

#include <array>
#include "QLearning.h"

class State {
public:
	State();
	~State();

private:
	std::array<double, QLearning::ACTION_MAX> scores;

};

#endif